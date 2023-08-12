#include "Actors/Weapon/STUProjectile.h"

#include <GameFramework/Character.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>

#include "Components/SphereComponent.h"


ASTUProjectile::ASTUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 3000.0f;
    MovementComponent->ProjectileGravityScale = 0.5f;
}

void ASTUProjectile::SetDirection(const FVector InDirection)
{
    Direction = InDirection;
}

void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
    MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
    SetLifeSpan(2.0f);
}

void ASTUProjectile::OnHit(UPrimitiveComponent* InHitComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, FVector InNormalImpulse, const FHitResult& InHit)
{
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Yellow, false, 1.0f);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), //
        DamageAmount,                               //
        GetActorLocation(),                         //
        Radius,                                     //
        UDamageType::StaticClass(),                 //
        {GetOwner()},                               //
        this,                                       //
        GetController(),                            //
        FullDamage);

    MovementComponent->StopMovementImmediately();
    Destroy();
}

APlayerController* ASTUProjectile::GetController() const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character)
    {
        return nullptr;
    }
    return Character->GetController<APlayerController>();
}
