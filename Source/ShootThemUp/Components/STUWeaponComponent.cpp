#include "Components/STUWeaponComponent.h"

#include <GameFramework/Character.h>

#include "Actors/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY(WeaponComp);

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    CreateWeapone();
}

void USTUWeaponComponent::StartFire()
{
    if(!CurrentWeapone)
    {
        return;
    }
    CurrentWeapone->StartFire();
}

void USTUWeaponComponent::StopFire()
{
    if (!CurrentWeapone)
    {
        return;
    }
    CurrentWeapone->StopFire();
}

void USTUWeaponComponent::CreateWeapone()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!ensure(IsValid(Character)))
    {
        return;
    }
    CurrentWeapone = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponeClass);
    if(!ensure(IsValid(CurrentWeapone)))
    {
        return;
    }
    FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapone->AttachToComponent(Character->GetMesh(), AttachmentRules, "WeaponSocket");
    CurrentWeapone->SetOwner(Character);
}
