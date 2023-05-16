
#include "STUBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer) 
    : Super(ObjectInitializer)
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
    InputValue.Y = InValue;
}

void ASTUBaseCharacter::MoveForward(IN float InValue)
{
    AddMovementInput(GetActorForwardVector(), InValue);
    InputValue.X = InValue;
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
}
