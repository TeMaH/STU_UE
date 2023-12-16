#include "AI/STUFindTargetService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"
#include "GameFramework/Character.h"

USTUFindTargetService::USTUFindTargetService()
{
    NodeName = "Find Target";
}

void USTUFindTargetService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if(const auto Controller = OwnerComp.GetAIOwner())
    {
        if(const auto PerceptionComponent = Controller->GetComponentByClass<USTUAIPerceptionComponent>())
        {
            if(const auto BlackboardComponent = OwnerComp.GetBlackboardComponent())
            {
                BlackboardComponent->SetValueAsObject(TargetKey.SelectedKeyName, PerceptionComponent->GetNearestCharacter());
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
