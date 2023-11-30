#include "Components/STUWeaponVFXComponent.h"

#include <NiagaraFunctionLibrary.h>

USTUWeaponVFXComponent::USTUWeaponVFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponVFXComponent::PlayVFX(const FHitResult& HitResult)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
}
