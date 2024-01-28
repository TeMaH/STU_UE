#include "STUGameModeBase.h"

#include "AIController.h"
#include "STUGameHUD.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();
    SpawnBots();
    RoundNum = 0;
    StartRound();
}

void ASTUGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUGameModeBase::StartRound()
{
    RoundTime = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(RondTimerHandle, this, &ThisClass::RoundTimeTick, 1.0f, true);
    const FString Msg = FString::Printf(TEXT("Start Round: %i ( %i / %i )"), RoundTime, RoundNum, GameData.RoundsNum);
    UKismetSystemLibrary::PrintString(GetWorld(), Msg);
}

void ASTUGameModeBase::RoundTimeTick()
{
    --RoundTime;
    const auto Msg = FString::Printf(TEXT("=== %i / %i ==="), RoundTime, GameData.RoundTime);
    UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, false, FLinearColor::White, 1.0f);
    if(RoundTime == 0)
    {
        if(++RoundNum < GameData.RoundsNum)
        {
            ResetPlayers();
            StartRound();
        }
        else
        {
            GetWorldTimerManager().ClearTimer(RondTimerHandle);
            UKismetSystemLibrary::PrintString(GetWorld(), TEXT("====== END GAME ====="), true, false, FLinearColor::Red, 10.0f);
        }
    }
}

void ASTUGameModeBase::ResetPlayers()
{
    if(!ensure(GetWorld()))
    {
        return;
    }
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if(Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::SpawnBots()
{
    const auto World = GetWorld();

    for(int32 i = 0; i < GameData.Players; i++)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto AIController = World->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);

        RestartPlayer(AIController);
    }
}
