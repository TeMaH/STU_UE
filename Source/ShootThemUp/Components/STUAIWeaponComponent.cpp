#include "Components/STUAIWeaponComponent.h"

void USTUAIWeaponComponent::StartFire()
{
     if(CurrentWeapone->IsAmmoEmpty())
     {
         EquipNextWeapon();
     }
     else
     {
         Super::StartFire();         
     }
}
