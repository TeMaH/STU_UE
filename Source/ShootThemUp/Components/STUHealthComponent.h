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
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable)
    bool IsDeath() const;

    UFUNCTION()
    void OnTakeAnyDamageCallback(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

    DECLARE_MULTICAST_DELEGATE(FOnDeath);
    FOnDeath OnDeath;

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, const float, const float);
    FOnHealthChanged OnHealthChanged;

public:
    bool TryAddHealth(const float Amount);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void ChangeHealthValue(const float InAmount);
    void PlayCameraShake();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal")
    float DelayBeforeHeal = 2.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal")
    float HealSpeed = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShakeVFX;


protected:
    float Health = 0.0f;
    float LastDamageTime = 0.0f;
};
