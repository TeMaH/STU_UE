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
    if(NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation))
    {
        BlackboardComponent->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
