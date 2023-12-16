#include "AI/STUFireService_BlackboardBase.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"

USTUFireService_BlackboardBase::USTUFireService_BlackboardBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "Fire";
}

void USTUFireService_BlackboardBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    const bool HasTarget = BlackBoard && BlackBoard->GetValueAsObject(GetSelectedBlackboardKey());
    if(const auto Controller = OwnerComp.GetAIOwner())
    {
        if(const auto WeaponComponent = Controller->GetPawn()->GetComponentByClass<USTUWeaponComponent>())
        {
            HasTarget ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
        
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
