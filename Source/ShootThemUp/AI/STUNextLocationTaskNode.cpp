// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUNextLocationTaskNode.h"

#include "AIController.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNextLocationTaskNode::USTUNextLocationTaskNode()
{
    NodeName = "Next Aim";
}

EBTNodeResult::Type USTUNextLocationTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if(!Controller || !BlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    const auto Pawn = Controller->GetPawn();
    if(!Pawn)
    {
        return EBTNodeResult::Failed;
    }
    const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
    if(!NavSystem)
    {
        return EBTNodeResult::Failed;
    }
    FNavLocation NavLocation;
    if(NavSystem->GetRandomReachablePointInRadius(GetCenter(OwnerComp), Radius, NavLocation))
    {
        BlackboardComponent->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

FVector USTUNextLocationTaskNode::GetCenter(const UBehaviorTreeComponent& OwnerComp) const
{
    if(SelfCenter)
    {
        if (const auto Controller = OwnerComp.GetAIOwner())
        {
            if(const auto Pawn = Controller->GetPawn())
            {
                return Pawn->GetActorLocation();
            }
        }
        return FVector::ZeroVector; 
    }
    const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent)
    {
        return FVector::ZeroVector;
    }
    const auto CenterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(CenterActorKey.SelectedKeyName));
    if (!CenterActor)
    {
        return FVector::ZeroVector;
    }
    return CenterActor->GetActorLocation();
}
