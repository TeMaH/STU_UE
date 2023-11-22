#pragma once

#include <CoreMinimal.h>

#include <Components/ActorComponent.h>

#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

DECLARE_LOG_CATEGORY_EXTERN(WeaponComp, Log, All);

USTRUCT(BlueprintType)
struct SHOOTTHEMUP_API FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<ASTUBaseWeapon> Class = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UAnimMontage* ReloadAnimMontage = nullptr;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();

    void StartFire();
    void StopFire();
    void EquipeNextWeapone();
    void ReloadWeapon();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

    void CreateWeapones();

    void AttachToSocket(AActor* Target, USceneComponent* SocketComponent, FName SocketName);
    void OnChangeWeaponeNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
    void OnReloadFinishedNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FName WeaponSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FName EquipmentSocketName = "EquipmentSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    TArray<FWeaponData> WeaponesData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapone")
    ASTUBaseWeapon* CurrentWeapone = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapone")
    TArray<ASTUBaseWeapon*> AllWeapones;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
    UAnimMontage* EquipMontage = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
    UAnimMontage* ReloadCurrentWeaponMontage = nullptr;

protected:
    int32 WeaponeIndex = 0;
    TWeakObjectPtr<USceneComponent> CharacterMesh = nullptr;
    TWeakObjectPtr<ACharacter> CharacterOwner = nullptr;
    bool IsChangeWeaponInProgress = false;
    bool IsReloadWeaponInProgress = false;

    template<typename T>
    T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation)
        {
            return nullptr;
        }
        for (auto AnimNotifyEvent : Animation->Notifies)
        {
            if (T* Notify = Cast<T>(AnimNotifyEvent.Notify))
            {
                return Notify;
            }
        }

        return nullptr;
    }
};
