#include "AI/Decorators/STUNeedDecorator.h"

#include "AIController.h"

#include "Actors/STUBaseWeapon.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUBaseCharacter.h"

USTUNeedDecorator::USTUNeedDecorator()
{
    NodeName = "Need Ammo";
}

bool USTUNeedDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    if(!WeaponClass)
    {
        return false;
    }
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller)
    {
        return false;
    }
    const auto Character = Controller->GetPawn<ASTUBaseCharacter>();
    if(!Character)
    {
        return false;
    }

    const auto WeaponComponent = Character->GetWeaponComponent();
    if(!WeaponComponent)
    {
        return false;
    }
    const FAmmoData& AmmoData = WeaponComponent->GetWeaponAmmoData(WeaponClass);
    return !AmmoData.Infinite && AmmoData.Bullets == 0 && AmmoData.Clips == 0;
}
