// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode.h"



UNodeBase* UStateNode::Match(TSubclassOf<UNodeBase> Type) const
{
    return Type == GetClass() ? const_cast<UStateNode*>(this):nullptr;
}

UNodeBase* UStateNode::FindNextState(TSubclassOf<UNodeBase> Type) const
{
    if (CanReentry && Type == GetClass()) return const_cast<UStateNode*>(this);
    else return UNodeBase::FindNextState(Type);
}
