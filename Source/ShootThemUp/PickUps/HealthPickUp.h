#pragma once

#include "CoreMinimal.h"

#include "PickUps/BasePickUp.h"

#include "HealthPickUp.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API AHealthPickUp : public ABasePickUp
{
    GENERATED_BODY()

protected:
    virtual bool GivePickUpTo(ASTUBaseCharacter* Character) override;

protected:
    UPROPERTY(EditAnywhere, meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float Health = 25.0f;
};
