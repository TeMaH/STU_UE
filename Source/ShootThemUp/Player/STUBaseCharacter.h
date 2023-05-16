// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "STUBaseCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

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
    float MouseSensitivityScale_Pitch = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    float MouseSensitivityScale_Yaw = 1.f;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    FVector2D InputValue = FVector2D::ZeroVector;

protected:
    virtual void BeginPlay() override;
    virtual void Turn(IN float InValue);
    virtual void LookUp(IN float InValue);
    virtual void MoveRight(IN float InValue);
    virtual void MoveForward(IN float InValue);


public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
