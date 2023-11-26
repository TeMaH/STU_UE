#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class ASTUBaseCharacter;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ABasePickUp : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABasePickUp();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere)
    USphereComponent* SphereComponent = nullptr;

    UPROPERTY(EditAnywhere)
    float RespawnTime = 5.0f;

 protected:
    virtual bool GivePickeUpTo(ASTUBaseCharacter* Character);

private:
    void MakePickUp();
    void RespawwnPickUp();
};
