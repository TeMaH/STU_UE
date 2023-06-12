#pragma once

#include "Actors/STUBaseWeapon.h"

#include <CoreMinimal.h>

#include "STURifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    void MakeShot();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
    float ShotInterval = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
    float Dispersion = 1.5f;

protected:
    FTimerHandle FireTimerHandle;
};
