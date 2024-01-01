#include "AI/Decorators/STUHealthPercentDecorator.h"

#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Player/STUBaseCharacter.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
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

    const auto HealthComponent = Character->GetHealthComponent();
    if(!HealthComponent || HealthComponent->IsDeath())
    {
        return false;
    }
    return HealthComponent->GetHealthPercent() < HealthPercent;
}
