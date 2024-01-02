#include "Components/STUWeaponComponent.h"

#include <GameFramework/Character.h>
#include <Kismet/KismetSystemLibrary.h>

#include "Actors/STUBaseWeapon.h"
#include "Animations/STUChangeWeapon_AnimNotify.h"
#include <Animations/STUReloadFinishedAnimNotify.h>

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
    WeaponIndex = 0;
    CreateWeapons();
    EquipNextWeapon();
    
    if (USTUChangeWeapon_AnimNotify* ChangeWeaponNotify = FindNotifyByClass<USTUChangeWeapon_AnimNotify>(EquipMontage))
    {
        ChangeWeaponNotify->OnAnimNotifyDelegate.AddUObject(this, &ThisClass::OnChangeWeaponNotify);
    }
    for (const auto WeaponData : WeaponesData)
    {
        if (USTUReloadFinishedAnimNotify* ReloadWeaponNotify = FindNotifyByClass<USTUReloadFinishedAnimNotify>(WeaponData.ReloadAnimMontage))
        {
            ReloadWeaponNotify->OnAnimNotifyDelegate.AddUObject(this, &ThisClass::OnReloadFinishedNotify);
        }
    }
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    StopFire();
    CurrentWeapone = nullptr;
    for (const auto WeaponItem : AllWeapones)
    {
        WeaponItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        WeaponItem->Destroy();
    }
    AllWeapones.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::CreateWeapons()
{
    const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    for (auto WeaponData : WeaponesData)
    {
        auto WeaponInstance = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponData.Class);
        if (!ensure(IsValid(WeaponInstance)))
        {
            continue;
        }
        AttachToSocket(WeaponInstance, CharacterMesh.Get(), EquipmentSocketName);
        WeaponInstance->SetOwner(GetOwner());
        WeaponInstance->OnClipEmptyDelegate.AddUObject(this, &ThisClass::ReloadWeapon);
        AllWeapones.Add(WeaponInstance);
    }
}

void USTUWeaponComponent::EquipWeapon(int32 InWeaponIndex)
{
    CurrentWeapone = AllWeapones[InWeaponIndex];
    AttachToSocket(CurrentWeapone, CharacterMesh.Get(), WeaponSocketName);
    IsChangeWeaponInProgress = false;
    const auto WeaponData = WeaponesData.FindByPredicate([&](const FWeaponData& Data) { return Data.Class == CurrentWeapone->GetClass(); });
    ReloadCurrentWeaponMontage = WeaponData->ReloadAnimMontage;
}

void USTUWeaponComponent::StartFire()
{
    if (!CurrentWeapone || IsChangeWeaponInProgress || IsReloadWeaponInProgress)
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

void USTUWeaponComponent::EquipNextWeapon()
{
    if (IsChangeWeaponInProgress || IsReloadWeaponInProgress)
    {
        return;
    }
    IsChangeWeaponInProgress = true;
    CharacterOwner->PlayAnimMontage(EquipMontage);
    StopFire();
}

void USTUWeaponComponent::ReloadWeapon()
{
    if (!CurrentWeapone->CanReload())
    {
        return;
    }
    StopFire();
    IsReloadWeaponInProgress = true;
    CharacterOwner->PlayAnimMontage(ReloadCurrentWeaponMontage);
}

bool USTUWeaponComponent::TryGetWeaponUIData(FWeaponUIData& OutData) const
{
    if (!CurrentWeapone)
    {
        return false;
    }
    OutData = CurrentWeapone->GetUIData();
    return true;
}

const FAmmoData& USTUWeaponComponent::GetCurrentWeaponAmmoData() const
{
    if (!CurrentWeapone)
    {
        return FAmmoData::Empty;
    }
    return CurrentWeapone->GetAmmoData();
}

const FAmmoData& USTUWeaponComponent::GetWeaponAmmoData(const TSubclassOf<ASTUBaseWeapon> InWeaponClass) const
{
    for (const auto WeaponItem : AllWeapones)
    {
        FString Msg = FString::Printf(TEXT("%s == %s"), *GetNameSafe(WeaponItem), *GetNameSafe(InWeaponClass));
        UKismetSystemLibrary::PrintString(GetWorld(), Msg);
        if(WeaponItem->IsA(InWeaponClass))
        {
            return WeaponItem->GetAmmoData();
        }
    }
    return FAmmoData::Empty;
}

bool USTUWeaponComponent::TryAddClips(TSubclassOf<ASTUBaseWeapon> WeaponClass, int32 Clips)
{
    for (const auto WeaponItem : AllWeapones)
    {
        if (WeaponItem && WeaponItem->IsA(WeaponClass))
        {
            return WeaponItem->TryToAddClips(Clips);
        }
    }
    return false;
}

void USTUWeaponComponent::AttachToSocket(AActor* InTarget, USceneComponent* InParent, FName InSocketName)
{
    const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    InTarget->AttachToComponent(InParent, AttachmentRules, InSocketName);
}

void USTUWeaponComponent::OnChangeWeaponNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp->GetOwner() != CharacterOwner)
    {
        return;
    }
    if (CurrentWeapone)
    {
        AttachToSocket(CurrentWeapone, CharacterMesh.Get(), EquipmentSocketName);
    }
    WeaponIndex = (WeaponIndex + 1) % AllWeapones.Num();
    EquipWeapon(WeaponIndex);
}

void USTUWeaponComponent::OnReloadFinishedNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    IsReloadWeaponInProgress = false;
    CurrentWeapone->ChangeClip();
}
