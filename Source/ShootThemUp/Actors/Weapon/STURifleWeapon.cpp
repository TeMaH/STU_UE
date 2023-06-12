#include "Actors/Weapon/STURifleWeapon.h"

#include <GameFramework/Character.h>

void ASTURifleWeapon::StartFire()
{
    Super::StartFire();
    GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ThisClass::MakeShot, ShotInterval, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    Super::StopFire();
    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character)
    {
        return;
    }
    const auto Controller = Character->GetController<APlayerController>();
    if (!Controller)
    {
        return;
    }
    FVector CameraLocation;
    FRotator CameraRotation;
    Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
    FTransform MuzzleSocket = MeshComponent->GetSocketTransform("MuzzleFlashSocket");
    const FVector Dir = FMath::VRandCone(CameraRotation.Vector(), FMath::DegreesToRadians(5.0f));
    FVector EndTraceLocation = CameraLocation + Dir * 1500.0f;
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndTraceLocation, ECollisionChannel::ECC_Visibility, Params);
    if (HitResult.bBlockingHit)
    {
        if (auto Target = Cast<ACharacter>(HitResult.GetActor()))
        {
            Target->TakeDamage(AmountDamage, FDamageEvent(DamageClass), Controller, GetOwner());
        }

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 16, FColor::Red, false, 2.0f);
        DrawDebugLine(GetWorld(), MuzzleSocket.GetLocation(), HitResult.ImpactPoint, FColor::Yellow, false, 2.0f);
    }
    else
    {
        DrawDebugLine(GetWorld(), MuzzleSocket.GetLocation(), EndTraceLocation, FColor::Green, false, 2.0f);
    }
}
