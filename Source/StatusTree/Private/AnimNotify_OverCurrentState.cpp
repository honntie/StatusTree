// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_OverCurrentState.h"


void UAnimNotify_OverCurrentState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	auto StatusTree = UStatusTreeComponent::FindOnOwner(MeshComp);
	if (!IsValid(StatusTree)) return;
	
	StatusTree->OverCurrent();
}
