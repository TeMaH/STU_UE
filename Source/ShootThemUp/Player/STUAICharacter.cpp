#include "Player/STUAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void ASTUAICharacter::OnDeath()
{
    if(const auto AIController = GetController<AAIController>())
    {
        AIController->BrainComponent->Cleanup();
    }
    Super::OnDeath();
}
