// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusTreeComponent.h"



// Sets default values for this component's properties
UStatusTreeComponent::UStatusTreeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UStatusTreeComponent::InitNode(UNodeBase* Target)
{
	if (!IsValid(Target)) return;
	_Foreach_Valid_Node_(Target->NextNodes, InitNode(Node);)
	Target->Init(this);
}

// Called when the game starts
void UStatusTreeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(RootStateNode))
	{
		UnregisterComponent();
		DestroyComponent();
		return;
	}
	InitNode(RootStateNode);
	EntryRoot();
}

void UStatusTreeComponent::EntryRoot()
{
	// 从外到内进入
	CurrentState = RootStateNode;
	TArray<UNodeBase*> EnterStatusLayers = CurrentState->GetStatusLayers();
	_Foreach_Valid_Node_(EnterStatusLayers, EnterStatusLayers.Last(i)->OnEnter();)
	CurrentState->OnEnter();
}

bool UStatusTreeComponent::OverCurrent()
{
	if (!CurrentState->IsExit) return false;
	
	// 从内到外退出
	TArray<UNodeBase*> StatusLayers = CurrentState->GetStatusLayers();
	CurrentState->OnExit();
	_Foreach_Valid_Node_(StatusLayers, Node->OnExit();)
	EntryRoot();
	
	return true;
}

UStateNode* UStatusTreeComponent::SwitchState(TSubclassOf<UStateNode> Type)
{
	UNodeBase* NewState = CurrentState->FindNextState(Type);
	if (!IsValid(NewState)) return nullptr;

	TArray<UNodeBase*> EnterStatusLayers = NewState->GetStatusLayers();    // 进入状态层
	TArray<UNodeBase*> ExitStatusLayers = CurrentState->GetStatusLayers();    // 退出状态层

	// 状态层差集
	while (EnterStatusLayers.Num() > 0 && ExitStatusLayers.Num() > 0)
	{
		if (EnterStatusLayers.Last(0) != ExitStatusLayers.Last(0)) break;
		EnterStatusLayers.RemoveAt(EnterStatusLayers.Num() - 1);
		ExitStatusLayers.RemoveAt(ExitStatusLayers.Num() - 1);
	}

	// 用满足NextNodes的状态做判断过渡条件
	const UNodeBase *LastNode = ExitStatusLayers.Num() == 0 ? CurrentState : ExitStatusLayers.Last(0);
	if (!LastNode->GetTransition(Type)) return nullptr;
	// 是否满足进入新状态条件
	else if (!NewState->GetCondition()) return nullptr;

	// 从内到外退出
	CurrentState->OnExit();
	_Foreach_Valid_Node_(ExitStatusLayers, Node->OnExit();)
	
	// 从外到内进入
	_Foreach_Valid_Node_(EnterStatusLayers, EnterStatusLayers.Last(i)->OnEnter();)
	NewState->OnEnter();
	
	CurrentState = Cast<UStateNode>(NewState);
	return CurrentState;
}

bool UStatusTreeComponent::IsCurrentState(TSubclassOf<UNodeBase> Type) const
{
	if (CurrentState->GetClass() == Type) return false;
	_Foreach_Valid_Node_(CurrentState->GetStatusLayers(), 
		if (Node->GetClass() == Type) return true;
	)
	return false;
}

// Called every frame
void UStatusTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsValid(CurrentState)) return;
	
	// 从外到内更新
	TArray<UNodeBase*> EnterStatusLayers = CurrentState->GetStatusLayers();
	_Foreach_Valid_Node_(EnterStatusLayers, EnterStatusLayers.Last(i)->OnUpdate(DeltaTime);)
	CurrentState->OnUpdate(DeltaTime);
}

UStatusTreeComponent* UStatusTreeComponent::FindOnOwner(const UActorComponent* Target)
{
	if (!Target) return nullptr;
	else if (!Target->GetOwner()) return nullptr;
	
	return Cast<UStatusTreeComponent>(Target->GetOwner()->GetComponentByClass(StaticClass()));
}

