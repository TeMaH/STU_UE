#include "Actors/Weapon/STURifleWeapon.h"

#include "Components/STUWeaponVFXComponent.h"

#include <GameFramework/Character.h>
#include <Engine/DamageEvents.h>

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponVFXComponent = CreateDefaultSubobject<USTUWeaponVFXComponent>("WeaponVFXComponent");
}

void ASTURifleWeapon::StartFire()
{
    Super::StartFire();
    GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ThisClass::MakeShot, ShotInterval, true);
    MakeShot();
    StartMuzzleVFX();
}

void ASTURifleWeapon::StopFire()
{
    Super::StopFire();
    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
    SetVisibilityMuzzleVFX(false);
}

void ASTURifleWeapon::MakeShot()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (IsAmmoEmpty())
    {
        StopFire();
        return;
    }
    if (!Character)
    {
        return;
    }
    FVector CameraLocation;
    FRotator CameraRotation;
    GetViewPoint(CameraLocation, CameraRotation);
    FTransform MuzzleSocket = MeshComponent->GetSocketTransform("MuzzleFlashSocket");
    const FVector Dir = FMath::VRandCone(CameraRotation.Vector(), FMath::DegreesToRadians(5.0f));
    FVector EndTraceLocation = CameraLocation + Dir * 1500.0f;
    FVector TraceVFXEnd = EndTraceLocation;
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    Params.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndTraceLocation, ECC_Visibility, Params);
    if (HitResult.bBlockingHit)
    {
        if (auto Target = Cast<ACharacter>(HitResult.GetActor()))
        {
            Target->TakeDamage(AmountDamage, FDamageEvent(DamageClass), Character->GetController(), GetOwner());
        }
        TraceVFXEnd = HitResult.ImpactPoint;
        WeaponVFXComponent->PlayVFX(HitResult);
    }
    SpawnTraceVFX(MuzzleSocket.GetLocation(), TraceVFXEnd);
    DecreaseAmmo();
}

void ASTURifleWeapon::StartMuzzleVFX()
{
    if(!MuzzleVFXComponent)
    {
        MuzzleVFXComponent = SpawnMuzzleVFX();
    }
    SetVisibilityMuzzleVFX(true);
}

void ASTURifleWeapon::SetVisibilityMuzzleVFX(const bool Visible) const
{
    if(!MuzzleVFXComponent)
    {
        return;
    }
    MuzzleVFXComponent->SetPaused(!Visible);
    MuzzleVFXComponent->SetVisibility(Visible);
}

void ASTURifleWeapon::SpawnTraceVFX(const FVector& TraceStart, const FVector& TraceEnd) const
{
    if(const auto TraceVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceVFX, TraceStart))
    {
        TraceVFXComponent->SetVariableVec3(TraceTargetName, TraceEnd);
    }
}

void ASTURifleWeapon::GetViewPoint(FVector& Location, FRotator& Rotator) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (const auto Controller = Character->GetController<APlayerController>())
    {
        Controller->GetPlayerViewPoint(Location, Rotator);
    }
    else
    {
        const FTransform MuzzleSocket = MeshComponent->GetSocketTransform("MuzzleFlashSocket");
        Location =  MuzzleSocket.GetTranslation();
        Rotator = MuzzleSocket.GetRotation().Rotator();
    }
}
