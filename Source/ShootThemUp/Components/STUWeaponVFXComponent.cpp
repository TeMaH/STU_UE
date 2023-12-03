#include "Components/STUWeaponVFXComponent.h"

#include <NiagaraFunctionLibrary.h>

USTUWeaponVFXComponent::USTUWeaponVFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponVFXComponent::PlayVFX(const FHitResult& HitResult)
{
    UNiagaraSystem* Effect = DefaultEffect;
    if (HitResult.PhysMaterial.IsValid() && Effects.Contains(HitResult.PhysMaterial.Get()))
    {
        Effect = Effects[HitResult.PhysMaterial.Get()];
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
}
