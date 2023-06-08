#include "Actors/STUBaseWeapone.h"

ASTUBaseWeapone::ASTUBaseWeapone()
{
    PrimaryActorTick.bCanEverTick = false;
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    SetRootComponent(MeshComponent);
}

void ASTUBaseWeapone::BeginPlay()
{
    Super::BeginPlay();
}
