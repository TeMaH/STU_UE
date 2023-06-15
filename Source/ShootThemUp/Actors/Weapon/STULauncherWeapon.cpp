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
    auto Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, MuzzleSocket);
    Projectile->SetDirection(MuzzleSocket.GetRotation().Vector());
    Projectile->FinishSpawning(MuzzleSocket);
}
