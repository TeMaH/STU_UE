#include "Actors/STUBaseWeapon.h"
#include <GameFramework/Character.h>

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

void ASTUBaseWeapon::StartFire()
{
    
}

void ASTUBaseWeapon::StopFire()
{
    
}
