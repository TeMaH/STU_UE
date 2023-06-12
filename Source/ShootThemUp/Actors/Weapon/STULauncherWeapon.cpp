#include "Actors/Weapon/STULauncherWeapon.h"

#include <Kismet/GameplayStatics.h>

#include "STUProjectile.h"


void ASTULauncherWeapon::StartFire()
{
    Super::StartFire();
    MakeShot();
}

void ASTULauncherWeapon::StopFire()
{
    Super::StopFire();
}

void ASTULauncherWeapon::MakeShot()
{
    FTransform MuzzleSocket = MeshComponent->GetSocketTransform("MuzzleFlashSocket");
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, MuzzleSocket);

    UGameplayStatics::FinishSpawningActor(Projectile, MuzzleSocket);
}
