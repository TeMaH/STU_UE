// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "STUGameModeBase.generated.h"

class ASTUBaseCharacter;
class AAIController;

USTRUCT(BlueprintType)
struct SHOOTTHEMUP_API FGameData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    int32 Players;
};


/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    virtual void StartPlay() override;
    
protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<AAIController> AIControllerClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ASTUBaseCharacter> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FGameData GameData;

    UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

private:
    void SpawnBots();
};
