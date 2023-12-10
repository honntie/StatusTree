// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeBase.h"
#include "StatusTreeComponent.h"
#include "UObject/NoExportTypes.h"
#include "StatusNode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class STATUSTREE_API UStatusNode : public UNodeBase
{
	GENERATED_BODY()

public:
	// UStatusNode(const FObjectInitializer& Initializer = FObjectInitializer::Get());
	
	UPROPERTY(EditDefaultsOnly, Instanced, Category="Nodes")
	TArray<class UNodeBase*> RootNodes;    // 根状态, 可进入的状态

	virtual void Init(UStatusTreeComponent *User) override;
	virtual UNodeBase* Match(TSubclassOf<UNodeBase> Type) const override;
};
