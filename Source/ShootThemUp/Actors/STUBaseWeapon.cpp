#include "Actors/STUBaseWeapon.h"

#include <GameFramework/Character.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY(Weapon);

const FAmmoData FAmmoData::Empty{0, 0, false};

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

const FAmmoData& ASTUBaseWeapon::GetAmmoData() const
{
    return CurrentAmmoData;
}

bool ASTUBaseWeapon::TryToAddClips(const float AmountClips)
{
    if (CurrentAmmoData.Infinite || IsFullAmmo() || AmountClips <= 0)
    {
        return false;
    }
    if (IsAmmoEmpty())
    {
        CurrentAmmoData.Clips = FMath::Min(AmountClips, DefaultAmmoData.Clips + 1);
        OnClipEmptyDelegate.Broadcast();
        return true;
    }
    const float NewAmountClips = CurrentAmmoData.Clips + AmountClips;
    if (DefaultAmmoData.Clips - NewAmountClips >= 0)
    {
        CurrentAmmoData.Clips = NewAmountClips;
    }
    else
    {
        CurrentAmmoData.Clips = DefaultAmmoData.Clips + 1;
        OnClipEmptyDelegate.Broadcast();
    }
    return true;
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

bool ASTUBaseWeapon::IsFullAmmo() const
{
    return CurrentAmmoData.Clips == DefaultAmmoData.Clips && CurrentAmmoData.Bullets == DefaultAmmoData.Bullets;
}

void ASTUBaseWeapon::StartFire() { }

void ASTUBaseWeapon::StopFire() { }

bool ASTUBaseWeapon::CanReload() const
{
    return CurrentAmmoData.Bullets < DefaultAmmoData.Bullets && CurrentAmmoData.Clips > 0;
}
