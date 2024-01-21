#include "PickUps/HealthPickUp.h"

#include "Components/STUHealthComponent.h"
#include "Player/STUBaseCharacter.h"

bool AHealthPickUp::GivePickUpTo(ASTUBaseCharacter* Character)
{
    if (!Character)
    {
        return false;
    }
    return Character->GetHealthComponent()->TryAddHealth(Health);
}
