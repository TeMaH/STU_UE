#include "STUBaseCharacter.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/TextRenderComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>

#include "Components/STUMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer) 
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthRender");
    TextRenderComponent->SetupAttachment(GetRootComponent());
    TextRenderComponent->bOwnerNoSee = true;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");

    TurnAxisName = TEXT("Turn");
    LookUpAxisName = TEXT("LookUp");
    MoveForwardAxisName = TEXT("MoveForward");
    MoveRightAxisName = TEXT("MoveRight");
    JumpName = TEXT("Jump");
    SprintName = TEXT("Sprint");
    FireName = TEXT("Fire");
}


void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    HealthComponent->OnDeath.AddUObject(this, &ThisClass::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ThisClass::OnHealthChnaged);
    UpdateHealthText(HealthComponent->GetHealth());
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

void ASTUBaseCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    const float VeloctiyZ = -GetVelocity().Z;
    if (VeloctiyZ < FallVelocityRange.X)
    {
        return;
    }
    const float FallDamage = FMath::GetMappedRangeValueClamped(FallVelocityRange, FallDamageRange, VeloctiyZ);
    UGameplayStatics::ApplyDamage(this, FallDamage, Controller, this, nullptr);
    FString Msg = FString::Printf(TEXT("Velocity = %.1f Damage = %.1f"), VeloctiyZ, FallDamage);
    UKismetSystemLibrary::PrintString(GetWorld(), Msg);
}

void ASTUBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUBaseCharacter::OnHealthChnaged(const float InHealth, const float InMaxHealth)
{
    UpdateHealthText(InHealth);
}

void ASTUBaseCharacter::UpdateHealthText(const float InHealth)
{
    TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), InHealth)));
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
    PlayerInputComponent->BindAction(FireName, IE_Released, WeaponComponent, &USTUWeaponComponent::Fire);
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
