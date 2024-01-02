#pragma once

#include <CoreMinimal.h>
#include "BehaviorTree/BTDecorator.h"
#include "STUNeedDecorator.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUNeedDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
    USTUNeedDecorator();
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ASTUBaseWeapon> WeaponClass = nullptr;

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
