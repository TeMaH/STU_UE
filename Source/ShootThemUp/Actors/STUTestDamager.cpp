#include "Actors/STUTestDamager.h"

#include <DrawDebugHelpers.h> 
#include <Kismet/GameplayStatics.h>

ASTUTestDamager::ASTUTestDamager()
{
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
    SetRootComponent(SceneComponent);
}

void ASTUTestDamager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUTestDamager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, Color);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFullDamage);
}

