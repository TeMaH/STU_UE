#include "Utils.h"

#include "STUPlayerState.h"

bool Utils::AreEnemy(const AController* ConntrollerA, const AController* ConntrollerB)
{
    if(ConntrollerA == ConntrollerB || !ConntrollerA || !ConntrollerB)
    {
        return false;
    }
    const auto PlayerStateA = ConntrollerA->GetPlayerState<ASTUPlayerState>();
    const auto PlayerStateB = ConntrollerB->GetPlayerState<ASTUPlayerState>();
    if(!PlayerStateA || !PlayerStateB) 
    {
        return false;
    }
    return PlayerStateA->GetTeamID() != PlayerStateB->GetTeamID();
}
