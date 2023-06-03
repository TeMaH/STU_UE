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
    if(DamageType->IsA<UIceDamageType>())
    {
        UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Cold"), true, false, FLinearColor::Blue);
    }
    else if (DamageType->IsA<UFireDamageType>())
    {
        UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hot"), true, false, FLinearColor::Red); 
    }
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