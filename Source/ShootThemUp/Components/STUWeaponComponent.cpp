#include "Components/STUWeaponComponent.h"

#include <GameFramework/Character.h>
#include <Kismet/KismetSystemLibrary.h>

#include "Actors/STUBaseWeapon.h"
#include "Animations/STUChangeWeapon_AnimNotify.h"

DEFINE_LOG_CATEGORY(WeaponComp);

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    CharacterOwner = Cast<ACharacter>(GetOwner());
    if (CharacterOwner.IsValid())
    {
        CharacterMesh = CharacterOwner->GetMesh();
    }
    WeaponeIndex = 0;
    CreateWeapones();
    EquipeNextWeapone();
    for (auto AnimNotifyEvent : EquipMontage->Notifies)
    {
        if (USTUChangeWeapon_AnimNotify* ChangeWeaponNotify = Cast<USTUChangeWeapon_AnimNotify>(AnimNotifyEvent.Notify))
        {
            ChangeWeaponNotify->OnAnimNotifyDelegate.AddUObject(this, &ThisClass::OnChangeWeaponeNotify);
            break;
        }
    }
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
    for (auto WeaponData : WeaponesData)
    {
        auto Weapone = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponData.Class);
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
    if (!CurrentWeapone || IsChangeWeaponInProgress)
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
    if (IsChangeWeaponInProgress)
    {
        return;
    }
    IsChangeWeaponInProgress = true;
    CharacterOwner->PlayAnimMontage(EquipMontage);
    StopFire();
}

void USTUWeaponComponent::RealoadWeapone()
{
    CharacterOwner->PlayAnimMontage(ReloadCurrentWeaponMontage);
}

void USTUWeaponComponent::AttachToSocket(AActor* InTarget, USceneComponent* InParent, FName InSocketName)
{
    FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    InTarget->AttachToComponent(InParent, AttachmentRules, InSocketName);
}

void USTUWeaponComponent::OnChangeWeaponeNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp->GetOwner() != CharacterOwner)
    {
        return;
    }
    if (CurrentWeapone)
    {
        AttachToSocket(CurrentWeapone, CharacterMesh.Get(), EquipmentSocketName);
    }
    WeaponeIndex = (WeaponeIndex + 1) % AllWeapones.Num();
    CurrentWeapone = AllWeapones[WeaponeIndex];
    AttachToSocket(CurrentWeapone, CharacterMesh.Get(), WeaponSocketName);
    IsChangeWeaponInProgress = false;
    auto WeaponData = WeaponesData.FindByPredicate([&](const FWeaponData& Data) { return Data.Class == CurrentWeapone->GetClass(); });
    ReloadCurrentWeaponMontage = WeaponData->ReloadAnimMontage;
}
