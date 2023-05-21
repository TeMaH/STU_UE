#include "STUMovementComponent.h"

#include "Player\STUBaseCharacter.h"

float USTUMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    if (const auto* Character = Cast<ASTUBaseCharacter>(GetOwner()))
    {
        return Character->IsSprintMovement() ? MaxSpeed * SprintCoeff : MaxSpeed;
    }
    return MaxSpeed;
}
