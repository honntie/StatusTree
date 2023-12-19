// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NodeBase.h"

#include "CoreMinimal.h"
#include "StateNode.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "StatusTreeComponent.generated.h"


UCLASS( meta=(BlueprintSpawnableComponent) )
class STATUSTREE_API UStatusTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UStateNode* RootStateNode;    // 初始根状态节点

	UPROPERTY(EditAnywhere)
	bool bIsDelayEnter = false;    // 将OnEnter延迟到与OnTick触发

	/**
	 * @brief 结束当前状态并重写进入RootState(该状态IsExit为True才可退出)
	 * @return 是否退出成功
	 */
	UFUNCTION(BlueprintCallable)
	bool OverCurrent();

	/**
	 * @brief 切换当前状态(旧)
	 * @param Type 需要切换的状态类型
	 * @return 是否切换成功
	 */
	// UFUNCTION(BlueprintCallable)
	// bool SwitchState(TSubclassOf<UStateNode> Type);

	/**
	 * @brief 切换当前状态
	 * @param Type 
	 * @return 返回切换后的状态, 如果切换失败则返回nullptr
	 */
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "Type"))
	UStateNode* SwitchState(TSubclassOf<UStateNode> Type);
	
	/**
	 * @brief 判断当前类型
	 * @param Type 需要判断的状态类型
	 * @param ReturnNode 返回当前状态
	 * @param IsSuccess 当前状态判断结果
	 */
	UFUNCTION(BlueprintCallable)
	bool IsCurrentState(TSubclassOf<UNodeBase> Type) const;
	
public:	
	// Sets default values for this component's properties
	UStatusTreeComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static UStatusTreeComponent* FindOnOwner(const UActorComponent* Target);
	
	/**
	 * @brief 初始化节点, 用于节点递归
	 * @param Target 被初始化的节点 
	 */
	void InitNode(UNodeBase* Target);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/**
	 * @brief 进入根状态
	 */
	void EntryRoot();
	
private:
	UStateNode* CurrentState = nullptr;    // 当前状态节点
	TArray<UNodeBase*> OnEnterStatusLayers;    // 储存需要进入的状态
};
