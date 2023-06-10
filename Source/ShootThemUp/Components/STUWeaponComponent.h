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
    
    void Fire();

protected:
    virtual void BeginPlay() override;

    void CreateWeapone();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    TSubclassOf<ASTUBaseWeapon> WeaponeClass = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapone")
    ASTUBaseWeapon* CurrentWeapone = nullptr;
};
