// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include <Actors\STUBaseWeapon.h>
#include <Components\STUWeaponComponent.h>

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

bool USTUPlayerHUDWidget::TryGetWeaponUIData(FWeaponUIData& OutData) const
{
    const auto PlayerPawn = GetOwningPlayerPawn();
    if (!PlayerPawn)
    {
        return false;
    }
    const auto WeaponComponent = PlayerPawn->GetComponentByClass<USTUWeaponComponent>();
    if (!WeaponComponent)
    {
        return false;
    }
    return WeaponComponent->TryGetWeaponUIData(OutData);
}
