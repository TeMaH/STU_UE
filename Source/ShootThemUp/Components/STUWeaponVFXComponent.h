#pragma once

#include <CoreMinimal.h>

#include "Components/ActorComponent.h"

#include "STUWeaponVFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

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
    UNiagaraSystem* DefaultEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    TMap<UPhysicalMaterial*, UNiagaraSystem*> Effects;
};
