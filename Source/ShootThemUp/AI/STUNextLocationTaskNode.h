// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
    USTUNextLocationTaskNode();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBlackboardKeySelector AimLocationKey;
};
