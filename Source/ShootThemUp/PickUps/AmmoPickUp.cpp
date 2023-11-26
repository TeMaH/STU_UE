#include "PickUps/AmmoPickUp.h"

#include "Components/STUWeaponComponent.h"
#include "Player/STUBaseCharacter.h"

bool AAmmoPickUp::GivePickeUpTo(ASTUBaseCharacter* Character)
{
    if (!Character)
    {
        return false;
    }
    return Character->GetWeaponComponent()->TryAddClips(WeaponClass, Clips);
}
