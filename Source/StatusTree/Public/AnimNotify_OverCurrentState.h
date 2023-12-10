// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusTreeComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_OverCurrentState.generated.h"

/**
 * 
 */
UCLASS()
class STATUSTREE_API UAnimNotify_OverCurrentState : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override { return "OverCurrentState"; }
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
