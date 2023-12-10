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

    ASTURifleWeapon();

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    void MakeShot();

    void StartMuzzleVFX();
    void SetVisibilityMuzzleVFX(const bool Visible) const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    class USTUWeaponVFXComponent* WeaponVFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
    float ShotInterval = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
    float Dispersion = 1.5f;

    TObjectPtr<UNiagaraComponent> MuzzleVFXComponent;

protected:
    FTimerHandle FireTimerHandle;
};
