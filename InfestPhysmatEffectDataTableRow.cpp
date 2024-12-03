#include "Gameplay/InfestPhysmatEffectDataTableRow.h"
#include "GameplayCueManager.h"

void FInfestPhysmatEffectDataTableRow::PlayPhysmatEffect(AActor* instigator, FHitResult hitResult, FGameplayTag ImpactGameplayCueNotifyTag, TObjectPtr<UDataTable> PhysmatGameplayCueNotifyDataTable)
{	
	if (instigator->GetNetMode() != NM_DedicatedServer) // If we are not on a dedicated server
	{
		if (ImpactGameplayCueNotifyTag != FGameplayTag::EmptyTag) // If the Impact tag is not empty
		{
			FGameplayTag currTag = ImpactGameplayCueNotifyTag;
			if (PhysmatGameplayCueNotifyDataTable) // If we have a defined Data Table to search
			{
				TArray<FInfestPhysmatEffectDataTableRow*> Rows;
				PhysmatGameplayCueNotifyDataTable->GetAllRows<FInfestPhysmatEffectDataTableRow>(TEXT("AInfestCharacter::CreateFootstepEffect"), Rows);
				for (const FInfestPhysmatEffectDataTableRow* Row : Rows)
				{
					if (Row && Row->ImpactTag == ImpactGameplayCueNotifyTag)
					{
						UPhysicalMaterial* PhysMat = hitResult.PhysMaterial.Get();

						if (PhysMat && PhysMat->SurfaceType == Row->SurfaceType) {
							currTag = Row->GameplayCueNotifyTag;
							break; // exact match, stop here
						}
						else if (Row->SurfaceType == EPhysicalSurface::SurfaceType_Default)
						{
							// default match, we set and keep going looking for an exact match
							currTag = Row->GameplayCueNotifyTag;
						}
					}
				}
			}
			FGameplayCueParameters params; // return param prep
			params.TargetAttachComponent = instigator->GetRootComponent();
			params.Location = hitResult.Location;
			params.SourceObject = instigator;
			params.EffectCauser = instigator;
			params.Normal = hitResult.ImpactNormal;
			params.PhysicalMaterial = hitResult.PhysMaterial.Get();

			UGameplayCueManager::ExecuteGameplayCue_NonReplicated(instigator, currTag, params);
		}
	}
}