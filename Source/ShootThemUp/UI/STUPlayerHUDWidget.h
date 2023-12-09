#pragma once

#include <CoreMinimal.h>

#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool TryGetWeaponUIData(FWeaponUIData& OutData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetAmmoData() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTackDamage(const float Health, const float Delta);

public:
    virtual bool Initialize() override;

protected:
    void OnHealthChanged(const float Health, const float Delta);
};
