// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUChangeWeaponService.h"

#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/STUBaseCharacter.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Value = FMath::RandRange(0.0f, 1.0f);
    const FString Msg =FString::Printf(TEXT("%f"), Value);
    UKismetSystemLibrary::PrintString(GetWorld(), Msg);
    if(Chance > Value)
    {
        if(const auto Controller = OwnerComp.GetAIOwner())
        {
            if(const auto AICharacter = Controller->GetPawn<ASTUBaseCharacter>())
            {
                if(const auto WeaponComponent = AICharacter->GetWeaponComponent())
                {
                    WeaponComponent->EquipNextWeapon();
                }
            }
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
