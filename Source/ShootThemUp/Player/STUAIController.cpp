// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUAIController.h"

#include "STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
    STUPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*STUPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if(const auto AICharacter = Cast<ASTUAICharacter>(InPawn))
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void ASTUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    SetFocus(STUPerceptionComponent->GetNearestCharacter());
}
