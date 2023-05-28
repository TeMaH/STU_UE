#include "Components/STUHealthComponent.h"

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
    Health = FMath::Max(0.0f, Health - Damage);
}

float USTUHealthComponent::GetHealth() const
{
    return Health;
}

float USTUHealthComponent::GetMaxHealth() const
{
    return MaxHealth;
}