// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeBase.h"
#include "StateNode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class STATUSTREE_API UStateNode : public UNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Property")
	bool CanReentry = false;    // 是否允许重写进入状态
	
	UPROPERTY(EditDefaultsOnly, Category="Property")
	bool IsExit = false;    // 是否可当做出口

	virtual UNodeBase* Match(TSubclassOf<UNodeBase> Type) const override;

	virtual UNodeBase* FindNextState(TSubclassOf<UNodeBase> Type) const override;
};
