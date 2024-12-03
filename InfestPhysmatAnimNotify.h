// Copyright (C) 2025 Atom Switch, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "Gameplay/InfestPhysmatEffectDataTableRow.h"
#include "InfestPhysmatAnimNotify.generated.h"

/** UInfestPhysmatAnimNotify
 *  Anim notify which triggers a query for a Physmat for relevent S/VFX.
 */
UCLASS()
class INFESTSTATIONGAME_API UInfestFootstepPhysmatAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:

	virtual void Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation) override;

	// Data table used for impact effect lookup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify|Footstep")
	TObjectPtr<UDataTable> FootstepGameplayCueNotifyDataTable;

	// Gameplay tag identifying the gameplay cue notify for this footstep
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify|Footstep")
	FGameplayTag ImpactGameplayCueNotifyTag;

	// Socket name we want to use when tracing for a PhysMat for footstep
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify|Footstep")
	FName traceSocketName;

	// The trace length we want to query the raycast downward for a PhysMat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify|Footstep")
	float traceLength = 50.f;
};
