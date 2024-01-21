#include "PickUps/BasePickUp.h"

#include "Components/SphereComponent.h"
#include "Player/STUBaseCharacter.h"

ABasePickUp::ABasePickUp()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    SphereComponent->InitSphereRadius(11.0f);
    SetRootComponent(SphereComponent);
}

// Called when the game starts or when spawned
void ABasePickUp::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABasePickUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABasePickUp::IsActive() const
{
    return !RespawnTimerHandler.IsValid();
}

bool ABasePickUp::GivePickUpTo(ASTUBaseCharacter* Character)
{
    return true;
}

void ABasePickUp::MakePickUp()
{
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);
    
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandler, this, &ThisClass::RespawnPickUp, RespawnTime);
}

void ABasePickUp::RespawnPickUp()
{
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
    RespawnTimerHandler.Invalidate();
}

void ABasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    if (ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(OtherActor))
    {
        if (GivePickUpTo(Character))
        {
            MakePickUp();
        }
    }
}
