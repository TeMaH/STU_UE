#include "Actors/STUBaseWeapon.h"

#include <GameFramework/Character.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY(Weapon);

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    SetRootComponent(MeshComponent);
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmoData = DefaultAmmoData;
}

void ASTUBaseWeapon::DecreaseAmmo()
{
    CurrentAmmoData.Bullets--;
    LogAmmoData();
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        ChangeClip();
    }
}

void ASTUBaseWeapon::ChangeClip()
{
    CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
    if (!CurrentAmmoData.Infinite)
    {
        CurrentAmmoData.Clips--;
    }
    UE_LOG(Weapon, Log, TEXT("---------- ChangeClip ----------"));
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmoData.Infinite && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmoData.Bullets == 0;
}

void ASTUBaseWeapon::LogAmmoData() const
{
    UE_LOGFMT(Weapon, Log, "Bullets = {0}, Clips = {1}, Infinite = {2}", CurrentAmmoData.Bullets, CurrentAmmoData.Clips, CurrentAmmoData.Infinite);
}

void ASTUBaseWeapon::StartFire()
{
    
}

void ASTUBaseWeapon::StopFire()
{
    
}
