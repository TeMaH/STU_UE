#pragma once

#include <CoreMinimal.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "STUMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    virtual float GetMaxSpeed() const override;

    bool IsSprint;

protected:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (ClampMin = "1.01", ClampMax = "2.0"))
    float SprintCoeff = 1.5f;
};
