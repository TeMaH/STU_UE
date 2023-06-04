#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>

#include "STUHealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();

    UFUNCTION(BlueprintCallable)
    float GetHealth() const;

    UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable)
    bool IsDeath() const;

    UFUNCTION()
    void OnTakeAnyDamageCallback(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
        class AController* InstigatedBy, AActor* DamageCauser);

    DECLARE_MULTICAST_DELEGATE(FOnDeath);
    FOnDeath OnDeath;

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, const float, const float);
    FOnHealthChanged OnHealthChanged;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 100.0f;

protected:
    float Health = 0.0f;
};
