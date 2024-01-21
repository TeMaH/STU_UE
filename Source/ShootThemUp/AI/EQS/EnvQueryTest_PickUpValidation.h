// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickUpValidation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickUpValidation : public UEnvQueryTest
{
    GENERATED_UCLASS_BODY()

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
