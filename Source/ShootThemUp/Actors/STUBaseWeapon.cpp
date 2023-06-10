#include "Actors/STUBaseWeapon.h"

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    SetRootComponent(MeshComponent);
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
