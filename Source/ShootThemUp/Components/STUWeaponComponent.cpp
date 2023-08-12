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
    if (const auto Character = Cast<ACharacter>(GetOwner()))
    {
        CharacterMesh = Character->GetMesh();
    }
    WeaponeIndex = 0;
    CreateWeapones();
    EquipeNextWeapone();
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    StopFire();
    CurrentWeapone = nullptr;
    for (auto Weapone : AllWeapones)
    {
        Weapone->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapone->Destroy();
    }
    AllWeapones.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::CreateWeapones()
{
    const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    for (auto WeaponeClass : WeaponeClasses)
    {
        auto Weapone = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponeClass);
        if (!ensure(IsValid(Weapone)))
        {
            continue;
        }
        AttachToSocket(Weapone, CharacterMesh.Get(), EquipmentSocketName);
        Weapone->SetOwner(GetOwner());
        AllWeapones.Add(Weapone);
    }
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

void USTUWeaponComponent::EquipeNextWeapone()
{
    StopFire();
    if (CurrentWeapone)
    {
        AttachToSocket(CurrentWeapone, CharacterMesh.Get(), EquipmentSocketName);
    }
    WeaponeIndex = (WeaponeIndex + 1) % AllWeapones.Num();
    CurrentWeapone = AllWeapones[WeaponeIndex];
    AttachToSocket(CurrentWeapone, CharacterMesh.Get(), WeaponSocketName);
}

void USTUWeaponComponent::AttachToSocket(AActor* InTarget, USceneComponent* InParent, FName InSocketName)
{
    FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    InTarget->AttachToComponent(InParent, AttachmentRules, InSocketName);
}
