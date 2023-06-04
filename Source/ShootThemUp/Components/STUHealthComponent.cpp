#include "STUHealthComponent.h"

#include "Actors/IceDamageType.h"
#include "Actors/FireDamageType.h"
#include <Kismet/KismetSystemLibrary.h>

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    Health = MaxHealth;
    auto Owner = GetOwner();
    Owner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamageCallback);
}

void USTUHealthComponent::OnTakeAnyDamageCallback(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0.0f || IsDeath())
    {
        return;
    }
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health, MaxHealth);
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

bool USTUHealthComponent::IsDeath() const
{
    return Health <= 0.0f;
}
