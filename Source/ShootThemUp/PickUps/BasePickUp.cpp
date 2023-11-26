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

void ABasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    if (Cast<ASTUBaseCharacter>(OtherActor))
    {
        Destroy();
    }
}
