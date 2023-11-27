#include "STUHealthComponent.h"

#include "Actors/IceDamageType.h"
#include "Actors/FireDamageType.h"
#include <Kismet/KismetSystemLibrary.h>

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool USTUHealthComponent::TryAddHealth(const float Amount)
{
    if (Health >= MaxHealth)
    {
        return false;
    }
    ChangeHealthValue(Amount);
    return true;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    Health = MaxHealth;
    auto Owner = GetOwner();
    Owner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamageCallback);
}

void USTUHealthComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(IsDeath())
    {
        return;
    }
    if (GetWorld()->RealTimeSeconds - LastDamageTime >= DelayBeforeHeal && Health < MaxHealth)
    {
        ChangeHealthValue(HealSpeed * DeltaTime);
    }
}

void USTUHealthComponent::ChangeHealthValue(const float InAmount)
{
    Health = FMath::Clamp(Health + InAmount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health, MaxHealth);
}

void USTUHealthComponent::OnTakeAnyDamageCallback(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0.0f || IsDeath())
    {
        return;
    }
    ChangeHealthValue(-Damage);
    LastDamageTime = GetWorld()->RealTimeSeconds;
    if(IsDeath())
    {
        OnDeath.Broadcast();
    }
}

float USTUHealthComponent::GetHealth() const
{
    return Health;
}

float USTUHealthComponent::GetMaxHealth() const
{
    return MaxHealth;
}

float USTUHealthComponent::GetHealthPercent() const
{
    return Health / MaxHealth;
}

bool USTUHealthComponent::IsDeath() const
{
    return Health <= 0.0f;
}
