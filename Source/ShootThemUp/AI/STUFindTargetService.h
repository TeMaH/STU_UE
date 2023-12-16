// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFindTargetService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUFindTargetService : public UBTService
{
	GENERATED_BODY()
public:
    USTUFindTargetService();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBlackboardKeySelector TargetKey;
	
};
