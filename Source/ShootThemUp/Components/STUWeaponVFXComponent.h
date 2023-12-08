#pragma once

#include <CoreMinimal.h>

#include "Components/ActorComponent.h"

#include "STUWeaponVFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

USTRUCT(BlueprintType)
struct SHOOTTHEMUP_API FDecalData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UMaterialInstance* Material = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FVector Size = FVector::ZeroVector;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float LifeTime = 1.0f;    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float FadeOutTime = 0.1f;
};

USTRUCT(BlueprintType)
struct SHOOTTHEMUP_API FImpactData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UNiagaraSystem* Effect = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FDecalData DecalData {nullptr, FVector::OneVector, 1.0f, 0.1f};
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponVFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponVFXComponent();

public:
    void PlayVFX(const FHitResult& HitResult);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    FImpactData DefaultImpactEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactEffects;
};
