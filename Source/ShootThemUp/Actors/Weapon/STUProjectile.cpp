#include "Actors/Weapon/STUProjectile.h"

#include "Components/SphereComponent.h"

#include <GameFramework/ProjectileMovementComponent.h>

ASTUProjectile::ASTUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.5f;
}

void ASTUProjectile::SetDirection(const FVector InDirection)
{
    Direction = InDirection;
}

void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();
    MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
    SetLifeSpan(2.0f);
}
