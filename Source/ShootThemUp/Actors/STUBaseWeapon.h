#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "STUBaseWeapon.generated.h"

class UNiagaraComponent;
DECLARE_LOG_CATEGORY_EXTERN(Weapon, Log, All);
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct SHOOTTHEMUP_API FAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;

    static const FAmmoData Empty;
};


USTRUCT(BlueprintType)
struct SHOOTTHEMUP_API FWeaponUIData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UTexture2D* MainIcon = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UTexture2D* CrossHairIcon = nullptr;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();
    
    virtual void StartFire();
    virtual void StopFire();
    virtual bool CanReload() const;
    void ChangeClip();

    FOnClipEmptySignature OnClipEmptyDelegate;

    FWeaponUIData GetUIData() const;
    const FAmmoData& GetAmmoData() const;
    bool TryToAddClips(const float AmountClips);

protected:
    virtual void BeginPlay() override;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void LogAmmoData() const;
    bool IsFullAmmo() const;


protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float AmountDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FAmmoData DefaultAmmoData{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    TSubclassOf<UDamageType> DamageClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    class UNiagaraSystem* MuzzleVFX;

    UNiagaraComponent* SpawnMuzzleVFX() const;
    
private:
    FAmmoData CurrentAmmoData;
};
