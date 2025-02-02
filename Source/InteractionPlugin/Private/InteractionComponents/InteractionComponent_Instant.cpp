// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponents/InteractionComponent_Instant.h"
#include "InteractorComponents/InteractorComponent.h"
#include "InteractionDataTypes.h"

UInteractionComponent_Instant::UInteractionComponent_Instant()
{
	PrimaryComponentTick.bCanEverTick = false;
	InteractionType = EInteractionType::IT_Instant;
}

bool UInteractionComponent_Instant::StartInteraction(UInteractorComponent *InteractorComp)
{
	/* Exit If Super Returns False */
	if (!Super::StartInteraction(InteractorComp))
	{
		return false;
	}

	/* Complete the Interaction Immediately*/
	CompleteInteraction(EInteractionResult::IR_Successful, InteractorComp);

	return true;
}
