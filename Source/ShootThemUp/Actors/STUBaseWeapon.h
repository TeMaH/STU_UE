#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "STUBaseWeapon.generated.h"

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

protected:
    virtual void BeginPlay() override;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void LogAmmoData() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float AmountDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FAmmoData DefaultAmmoData{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    TSubclassOf<UDamageType> DamageClass;

private:
    FAmmoData CurrentAmmoData;
};
