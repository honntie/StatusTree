// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateNode.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SwitchState.generated.h"

/**
 * 
 */
UCLASS()
class STATUSTREE_API UAnimNotify_SwitchState : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStateNode> StateType = UStateNode::StaticClass();

	virtual FString GetNotifyName_Implementation() const override { return StateType->GetDisplayNameText().ToString(); }
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
