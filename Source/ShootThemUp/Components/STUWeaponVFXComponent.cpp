#include "Components/STUWeaponVFXComponent.h"

#include <NiagaraFunctionLibrary.h>

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

USTUWeaponVFXComponent::USTUWeaponVFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponVFXComponent::PlayVFX(const FHitResult& HitResult)
{
    FImpactData& ImpactEffect = DefaultImpactEffect;
    if (HitResult.PhysMaterial.IsValid() && ImpactEffects.Contains(HitResult.PhysMaterial.Get()))
    {
        ImpactEffect = ImpactEffects[HitResult.PhysMaterial.Get()];
    }

    auto Rot =HitResult.ImpactNormal.Rotation(); 
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ImpactEffect.Effect,
        HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation());
    if(UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(),
        ImpactEffect.DecalData.Material,
        ImpactEffect.DecalData.Size,
        HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation()))
    {
        UKismetSystemLibrary::PrintString(GetWorld(), Decal->GetComponentRotation().ToString());
        UKismetSystemLibrary::PrintString(GetWorld(), Decal->GetName());
        UKismetSystemLibrary::PrintString(GetWorld(), Decal->GetComponentLocation().ToString());
        Decal->SetFadeOut(ImpactEffect.DecalData.LifeTime, ImpactEffect.DecalData.FadeOutTime);
    }
}
