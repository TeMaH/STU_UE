#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "STUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/STUAICharacter.h"

ACharacter* USTUAIPerceptionComponent::GetNearestCharacter() const
{
    TArray<AActor*> Enemies;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Enemies);
    if(Enemies.Num() == 0)
    {
        return nullptr;
    }

    const auto Controller = Cast<AAIController>(GetOwner());
    if(!Controller)
    {
        return nullptr;
    }

    const auto AICharacter = Controller->GetPawn<ASTUAICharacter>();
    if(!AICharacter)
    {
        return nullptr;
    }
    float BestDistance = MAX_FLT;
    AActor* NearestCharacter = nullptr;
    for(AActor* Enemy : Enemies)
    {
        const auto HealthComponent = Enemy->GetComponentByClass<USTUHealthComponent>();
        if(HealthComponent && !HealthComponent->IsDeath())
        {
            const auto CurrentDistance = FVector::Dist(AICharacter->GetActorLocation(), Enemy->GetActorLocation());
            if(CurrentDistance < BestDistance)
            {
                NearestCharacter = Enemy;
                BestDistance = CurrentDistance;
            }
        }
    }
    return Cast<ACharacter>(NearestCharacter);
}
