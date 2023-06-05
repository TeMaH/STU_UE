// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "STUBaseCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class USTUHealthComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* TextRenderComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName LookUpAxisName = "";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName TurnAxisName = "";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName MoveForwardAxisName = "";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName MoveRightAxisName = "";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName JumpName = "";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName SprintName = "";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    float MouseSensitivityScale_Pitch = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    float MouseSensitivityScale_Yaw = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    UAnimMontage* DeathMontage = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FVector2D FallVelocityRange = FVector2D(650.0f, 950.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FVector2D FallDamageRange = FVector2D(15.0f, 45.0f);

    bool IsSprint = false;

protected:
    virtual void BeginPlay() override;
    virtual void Turn(IN float InValue);
    virtual void LookUp(IN float InValue);
    virtual void MoveRight(IN float InValue);
    virtual void MoveForward(IN float InValue);
    virtual void SprintStarted();
    virtual void SprintEnded();
    virtual void Landed(const FHitResult& Hit);

    void OnDeath();
    void OnHealthChnaged(const float InHealth, const float InMaxHealth);
    void UpdateHealthText(const float InHealth);

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
    bool IsSprintMovement() const;

    UFUNCTION(BlueprintCallable)
    float GetRotation() const;
};
