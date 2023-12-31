#include "AI/EQS/STUEnemyEnvQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if(!Blackboard)
    {
        return;
    }

    const auto Target =  Cast<AActor>(Blackboard->GetValueAsObject("Target"));
    if(!Target)
    {
        return;
    }
 	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Target);   
}
