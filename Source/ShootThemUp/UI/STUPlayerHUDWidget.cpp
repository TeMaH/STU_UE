#include "STUPlayerHUDWidget.h"

#include "Actors/STUBaseWeapon.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUBaseCharacter.h"

bool USTUPlayerHUDWidget::Initialize()
{
    if(const auto* Player = GetOwningPlayerPawn<ASTUBaseCharacter>())
    {
        Player->GetHealthComponent()->OnHealthChanged.AddUObject(this, &ThisClass::OnHealthChanged);
    }
    return Super::Initialize();
}

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto* Player = GetOwningPlayerPawn<ASTUBaseCharacter>(); 
    if (!Player)
    {
        return 0.0f;
    }
    const auto* HealthComponent = Player->GetHealthComponent();
    if (!HealthComponent)
    {
        return 0.0f;
    }
    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::TryGetWeaponUIData(FWeaponUIData& OutData) const
{
    const auto* Player = GetOwningPlayerPawn<ASTUBaseCharacter>(); 
    if (!Player)
    {
        return false;
    }
    const auto* WeaponComponent = Player->GetWeaponComponent();
    if (!WeaponComponent)
    {
        return false;
    }
    return WeaponComponent->TryGetWeaponUIData(OutData);
}

FString USTUPlayerHUDWidget::GetAmmoData() const
{
    const auto* Player = GetOwningPlayerPawn<ASTUBaseCharacter>();
    if (!Player)
    {
        return "";
    }
    const auto* WeaponComponent = Player->GetWeaponComponent();
    if (!WeaponComponent)
    {
        return "";
    }
    const FAmmoData& AmmoData = WeaponComponent->GetCurrentWeaponAmmoData();
    if (AmmoData.Infinite)
    {
        return FString::Printf(TEXT("%i / ∞"), AmmoData.Bullets);
    }
    else
    {
        return FString::Printf(TEXT("%i / %i"), AmmoData.Bullets, AmmoData.Clips);
    }

}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto* Player = GetOwningPlayerPawn<ASTUBaseCharacter>();
    if (!Player)
    {
        return false;
    }
    return !Player->GetHealthComponent()->IsDeath();
}

bool USTUPlayerHUDWidget::IsSpectating() const
{
    const auto* Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTUPlayerHUDWidget::OnHealthChanged(const float Health, const float Delta)
{
    if(Delta < 0.0f)
    {
        OnTackDamage(Health, Delta);
    }
}
