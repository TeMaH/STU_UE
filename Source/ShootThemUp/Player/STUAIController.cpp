// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUAIController.h"

#include "STUAICharacter.h"

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if(const auto AICharacter = Cast<ASTUAICharacter>(InPawn))
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}
