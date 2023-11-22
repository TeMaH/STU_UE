// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto PlayerPawn = GetOwningPlayerPawn(); 
    if (!PlayerPawn)
    {
        return 0.0f;
    }
    const auto HealthComponent = PlayerPawn->GetComponentByClass<USTUHealthComponent>();
    if (!HealthComponent)
    {
        return 0.0f;
    }
    return HealthComponent->GetHealthPercent();
}
