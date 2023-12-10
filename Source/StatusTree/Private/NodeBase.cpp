// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBase.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<UNodeBase*> UNodeBase::GetStatusLayers() const
{
    TArray<UNodeBase*> Result;
    UNodeBase* TempStatus = Status;

    // 将Status加入Result
    while (IsValid(TempStatus))
    {
        Result.Add(TempStatus);
        TempStatus = TempStatus->Status;
    }
    return Result;
}

UNodeBase* UNodeBase::FindNextState(TSubclassOf<UNodeBase> Type) const
{
    // 尝试在NextNodes寻找下一个状态
    UNodeBase* Result = nullptr;
    _Foreach_Valid_Node_(NextNodes, 
        Result = Node->Match(Type);
        if (IsValid(Result)) return Result;
    )
    
    // 在Status寻找下一个状态
    if (IsValid(Status)) return Status->FindNextState(Type);
    
    return nullptr;
}

UNodeBase* UNodeBase::GetStatus(TSubclassOf<UNodeBase> Type) const
{
    if (Type == GetClass()) return const_cast<UNodeBase*>(this);     // 返回自身
    else if (!IsValid(Status)) return nullptr;    // 无归属状态
    else return Status->GetStatus(Type);    // 返回归属状态
}

void UNodeBase::Init(UStatusTreeComponent* User)
{
    // NextNodes的左右两侧链接
    _Foreach_Valid_Node_(NextNodes,
        if (Node->LinkPrev && i > 0) Node->NextNodes.Add(NextNodes[i - 1]);
        if (Node->LinkNext && i < NextNodes.Num() - 1) Node->NextNodes.Add(NextNodes[i + 1]);
        if (Node->LinkLast) Node->NextNodes.Add(this);
    )
    StatusTree = User;
    OnInit();
}

void UNodeBase::SetStatus(UNodeBase* StatusNode)
{
    Status = StatusNode;
    _Foreach_Valid_Node_(NextNodes, Node->SetStatus(StatusNode);)    // 设置下一个节点们的Status
}

