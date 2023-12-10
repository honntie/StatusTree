// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusNode.h"
#include "Kismet/KismetSystemLibrary.h"

void UStatusNode::Init(UStatusTreeComponent *User)
{
     // 链接根节点的两侧, 初始化根节点
     _Foreach_Valid_Node_(RootNodes,
         Node->SetStatus(this);    // 设置根节点的Status
         User->InitNode(Node);    // 初始化节点, 再链接
         
         // 链接根节点
         if (Node->LinkPrev && i > 0) Node->NextNodes.Add(RootNodes[i - 1]);
         if (Node->LinkNext && i < RootNodes.Num() - 1) Node->NextNodes.Add(RootNodes[i + 1]);
     )

    Super::Init(User);    // 处理NextNodes的链接再初始化自身
}

UNodeBase* UStatusNode::Match(TSubclassOf<UNodeBase> Type) const
{
    // 匹配规则改成匹配根节点
    UNodeBase* Result = nullptr;
    _Foreach_Valid_Node_(RootNodes,
        Result = Node->Match(Type);
        if (IsValid(Result)) return Result;
    )
    return nullptr;
}
