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

FWeaponUIData ASTUBaseWeapon::GetUIData() const
{
    return UIData;
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
        OnClipEmptyDelegate.Broadcast();
    }
}

void ASTUBaseWeapon::ChangeClip()
{
    if (!CurrentAmmoData.Infinite)
    {
        if (CurrentAmmoData.Clips == 0)
        {
            return;
        }
        CurrentAmmoData.Clips--;
    }
    CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
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

bool ASTUBaseWeapon::CanReload() const
{
    return CurrentAmmoData.Bullets < DefaultAmmoData.Bullets && CurrentAmmoData.Clips > 0;
}
