// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "InteractorComponents/InteractorComponent.h"
#include "Interface/InteractionInterface.h"

DEFINE_LOG_CATEGORY(LogInteraction);

UInteractionComponent::UInteractionComponent()
	:InteractionType(EInteractionType::IT_None)
	,bMultipleInteraction(true)
{

}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::SetInteractionFocusState(bool bNewFocus)
{
	if (OnInteractionFocusChanged.IsBound())
	{
		OnInteractionFocusChanged.Broadcast(bNewFocus);
	}
}

bool UInteractionComponent::StartInteraction(UInteractorComponent* InteractorComp)
{
	/* Validate Interactor Comp */
	if (!IsValid(InteractorComp))
	{
		UE_LOG(LogInteraction, Warning, TEXT("Failed to Start Interaction Due to Invalid Interactor Component"));
		return false;
	}

	return true;
}

bool UInteractionComponent::StopInteraction(UInteractorComponent* InteractorComp)
{
	/* Validate Interactor Comp */
	if (!IsValid(InteractorComp))
	{
		UE_LOG(LogInteraction, Warning, TEXT("Failed to Stop Interaction Due to Invalid Interactor Component"));
		return false;
	}

	return true;
}

bool UInteractionComponent::CanInteractWith(UInteractorComponent* InteractorComp)
{

	/* Get Owner */
	AActor* Owner = GetOwner();

	/* Check for Interaction Interface and Execute If Owner Implements */
	if (IsValid(Owner) &&
		Owner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		return IInteractionInterface::Execute_CanInteractWith(Owner, InteractorComp->GetOwner());
	}

	return true;
}

void UInteractionComponent::CompleteInteraction(EInteractionResult InteractionResult, UInteractorComponent* InteractorComp)
{
	/* Validate Interactor Comp */
	if (IsValid(InteractorComp))
	{
		/* Invoke Interactor End Interaction */
		InteractorComp->EndInteraction(InteractionResult, this);
	}
}
