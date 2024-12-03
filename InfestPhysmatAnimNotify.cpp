// Copyright (C) 2025 Atom Switch, Inc.

#include "InfestPhysmatAnimNotify.h"
#include "Character\InfestCharacter.h"
#include "Components\CapsuleComponent.h"

void UInfestFootstepPhysmatAnimNotify::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	// Define Raycast Start Location (optional adjustment)
	FVector StartLocation;
	if (!traceSocketName.IsNone()) {
		if (meshComp->DoesSocketExist(traceSocketName)) {
			StartLocation = meshComp->GetSocketLocation(traceSocketName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Notify Socket Name Was Not Found."));
		}
	}
	else
	{
		StartLocation = meshComp->GetComponentLocation(); // Assuming starting point at mesh component location
	}
	FVector EndLocation = StartLocation + FVector::DownVector * traceLength; // Trace downwards for traceLength distance.
	TArray<FHitResult> OutHits;
	FCollisionQueryParams TraceParams(TEXT("FootstepRaycast"), true, meshComp->GetOwner()); // trace parameters
	TraceParams.bReturnPhysicalMaterial = true;

	// Perform Raycast
	meshComp->GetWorld()->LineTraceMultiByChannel(OutHits, StartLocation, EndLocation, ECC_WorldStatic, TraceParams);

	// Check Result
	if (OutHits.Num() > 0)
	{
		// Get hit result information
		FInfestPhysmatEffectDataTableRow::PlayPhysmatEffect(meshComp->GetOwner(), OutHits[0], ImpactGameplayCueNotifyTag, FootstepGameplayCueNotifyDataTable);
	}
}
