// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASTUProjectile();

    void SetDirection(const FVector InDirection);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* InHitComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, FVector InNormalImpulse, const FHitResult& InHit );
    
    APlayerController* GetController() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    class USTUWeaponVFXComponent* WeaponVFXComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float DamageAmount = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float Radius = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    bool FullDamage = false;

protected:
    FVector Direction = FVector::ZeroVector;
};
