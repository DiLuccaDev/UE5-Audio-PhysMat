// Copyright (C) 2025 Atom Switch, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameplayCueInterface.h"
#include "GameplayCueManager.h"
#include "Gameplay/ModifiableValues/InfestModifiableObjectInterface.h"
#include "InfestPhysmatEffectDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct INFESTSTATIONGAME_API FInfestPhysmatEffectDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	// The impact tag provided by the projectile for looking up the appropriate gameplay cue
	UPROPERTY(EditDefaultsOnly, Category = "Physmat")
	FGameplayTag ImpactTag;

	// The type of surface this impact effect is relevant for
	UPROPERTY(EditDefaultsOnly, Category = "Physmat")
	TEnumAsByte<EPhysicalSurface> SurfaceType = EPhysicalSurface::SurfaceType_Default;

	// The gameplay cue that will fire if this impact effect is resolved
	UPROPERTY(EditDefaultsOnly, Category = "Physmat")
	FGameplayTag GameplayCueNotifyTag;

	static void PlayPhysmatEffect(AActor* instigator, FHitResult hitResult, FGameplayTag ImpactGameplayCueNotifyTag, TObjectPtr<UDataTable> PhysmatGameplayCueNotifyDataTable);
};
