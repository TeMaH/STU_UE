#include "STUBaseCharacter.h"

#include "Animation/STUMovementComponent.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer) 
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    TurnAxisName = TEXT("Turn");
    LookUpAxisName = TEXT("LookUp");
    MoveForwardAxisName = TEXT("MoveForward");
    MoveRightAxisName = TEXT("MoveRight");
    JumpName = TEXT("Jump");
    SprintName = TEXT("Sprint");
}


void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUBaseCharacter::Turn(IN float InValue)
{
    AddControllerYawInput(InValue * MouseSensitivityScale_Yaw);
}

void ASTUBaseCharacter::LookUp(IN float InValue)
{
    AddControllerPitchInput(InValue * MouseSensitivityScale_Pitch);
}

void ASTUBaseCharacter::MoveRight(IN float InValue)
{
    AddMovementInput(GetActorRightVector(), InValue);
}

void ASTUBaseCharacter::MoveForward(IN float InValue)
{
    AddMovementInput(GetActorForwardVector(), InValue);
}

void ASTUBaseCharacter::SprintStarted()
{
    IsSprint = true;
}

void ASTUBaseCharacter::SprintEnded()
{
    IsSprint = false;
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TurnAxisName, this, &ASTUBaseCharacter::Turn);
    PlayerInputComponent->BindAxis(LookUpAxisName, this, &ASTUBaseCharacter::LookUp);
    PlayerInputComponent->BindAxis(MoveForwardAxisName, this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis(MoveRightAxisName, this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAction(JumpName, IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction(SprintName, IE_Pressed, this, &ASTUBaseCharacter::SprintStarted);
    PlayerInputComponent->BindAction(SprintName, IE_Released, this, &ASTUBaseCharacter::SprintEnded);
}

bool ASTUBaseCharacter::IsSprintMovement() const
{
    return !GetVelocity().IsNearlyZero() && IsSprint;
}

float ASTUBaseCharacter::GetRotation() const
{
    const FVector Velocity = GetVelocity();
    if (Velocity.IsNearlyZero())
    {
        return 0.0f;
    }
    const FVector Forward = GetActorForwardVector();

    const float Dot = FVector::DotProduct(Forward, Velocity.GetSafeNormal2D());
    const FVector Cross = FVector::CrossProduct(Forward, Velocity.GetSafeNormal2D());
    const float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));
    return Cross.Z < 0.0f ? -Angle : Angle;
}
