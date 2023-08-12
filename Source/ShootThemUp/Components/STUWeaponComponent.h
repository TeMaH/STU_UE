#pragma once

#include <CoreMinimal.h>

#include <Components/ActorComponent.h>

#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

DECLARE_LOG_CATEGORY_EXTERN(WeaponComp, Log, All);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();

    void StartFire();
    void StopFire();
    void EquipeNextWeapone();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

    void CreateWeapones();

    void AttachToSocket(AActor* Target, USceneComponent* SocketComponent, FName SocketName);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FName WeaponSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FName EquipmentSocketName = "EquipmentSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    TArray<TSubclassOf<ASTUBaseWeapon>> WeaponeClasses;

    /*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    TSubclassOf<ASTUBaseWeapon> WeaponeClass = nullptr;*/

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapone")
    ASTUBaseWeapon* CurrentWeapone = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapone")
    TArray<ASTUBaseWeapon*> AllWeapones;

protected:
    int32 WeaponeIndex = 0;
    TWeakObjectPtr<USceneComponent> CharacterMesh = nullptr;
};
