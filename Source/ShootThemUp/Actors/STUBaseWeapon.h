#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();
    
    bool TryFire();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MeshComponent;

protected:
    virtual void BeginPlay() override;

    void MakeShot();
};
