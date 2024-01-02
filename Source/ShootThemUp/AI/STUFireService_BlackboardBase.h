// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "STUFireService_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUFireService_BlackboardBase : public UBTService_BlackboardBase
{
    GENERATED_UCLASS_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsActive = true;

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
