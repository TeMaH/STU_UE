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
};
