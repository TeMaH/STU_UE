#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();
    
    void StartFire();
    void StopFire();

    bool TryFire();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float AmountDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    TSubclassOf<UDamageType> DamageClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
    float ShotInterval = 0.5f;

protected:
    virtual void BeginPlay() override;

    void MakeShot();

protected:
    FTimerHandle FireTimerHandle;
};
