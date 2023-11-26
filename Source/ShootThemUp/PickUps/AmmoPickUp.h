#pragma once

#include "CoreMinimal.h"
#include "PickUps/BasePickUp.h"
#include "AmmoPickUp.generated.h"

/**
 *
 */
class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API AAmmoPickUp : public ABasePickUp
{
    GENERATED_BODY()

protected:
    virtual bool GivePickeUpTo(ASTUBaseCharacter* Character) override;

protected:
    UPROPERTY(EditAnywhere)
    TSubclassOf<ASTUBaseWeapon> WeaponClass = nullptr;

    UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 10))
    int32 Clips = 1;
};
