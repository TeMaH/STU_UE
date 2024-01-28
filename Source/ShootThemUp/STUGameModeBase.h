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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game, meta = (ClampMin = 1, ClampMax = 4))
    int32 Players;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game, meta = (ClampMin = 1, ClampMax = 10))
    int32 RoundsNum;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game, meta = (ClampMin = 3, ClampMax = 300))
    int32 RoundTime;
};

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    virtual void StartPlay() override;
    
protected:
    virtual void BeginPlay() override;

    void StartRound();
    void RoundTimeTick();
    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<AAIController> AIControllerClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ASTUBaseCharacter> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FGameData GameData;

    UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    int32 RoundTime = 0;
    int32 RoundNum = 0;
    FTimerHandle RondTimerHandle;

private:
    void SpawnBots();
};
