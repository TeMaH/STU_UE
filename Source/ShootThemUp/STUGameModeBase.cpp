// Fill out your copyright notice in the Description page of Project Settings.

#include "STUGameModeBase.h"

#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
}

void ASTUGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    int32 Variable = 0;
    if (Variable < 0)
    {
        for (int32 i = 0; i < 10; i++)
        {
            UE_LOG(LogTemp, Warning, TEXT("index i: %i"), i);
        }
    }
}
