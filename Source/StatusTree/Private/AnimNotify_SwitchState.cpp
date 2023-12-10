// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SwitchState.h"

#include "StatusTreeComponent.h"

void UAnimNotify_SwitchState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UStatusTreeComponent* StatusTree = UStatusTreeComponent::FindOnOwner(MeshComp);
	if (!IsValid(StatusTree)) return;
	
	StatusTree->SwitchState(StateType);
}
