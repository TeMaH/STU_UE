#include "AI/EQS/EnvQueryTest_PickUpValidation.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "PickUps/BasePickUp.h"

UEnvQueryTest_PickUpValidation::UEnvQueryTest_PickUpValidation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::High;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickUpValidation::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool WantsBeValid = BoolValue.GetValue();
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        if(!ItemActor)
        {
            continue;
        }
        const ABasePickUp* PickUp = Cast<ABasePickUp>(ItemActor);
        if(!PickUp)
        {
            continue;
        }
        It.SetScore(TestPurpose, FilterType, PickUp->IsActive(), WantsBeValid);
    }
}
