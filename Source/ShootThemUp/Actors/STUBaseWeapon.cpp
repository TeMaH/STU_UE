#include "Actors/STUBaseWeapon.h"
#include <GameFramework/Character.h>

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    SetRootComponent(MeshComponent);
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

bool ASTUBaseWeapon::TryFire()
{
    MakeShot();
    return true;
}

void ASTUBaseWeapon::MakeShot()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character)
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
    
    FVector EndTraceLocation = CameraLocation + CameraRotation.Vector() * 1500.0f;
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndTraceLocation, ECollisionChannel::ECC_Visibility, Params);
    if(HitResult.bBlockingHit)
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
