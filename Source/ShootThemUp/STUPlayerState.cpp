#include "STUPlayerState.h"

#include "Player/STUBaseCharacter.h"

void ASTUPlayerState::SetTeamID(const int32 ID)
{
    TeamID = ID;
}

int32 ASTUPlayerState::GetTeamID() const
{
    return TeamID;
}

void ASTUPlayerState::SetTeamColor(const FLinearColor& Color)
{
    TeamColor = Color;
    
}

const FLinearColor& ASTUPlayerState::GetTeamColor() const
{
    return TeamColor;
}
