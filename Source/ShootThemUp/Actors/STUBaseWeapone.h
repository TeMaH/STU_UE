#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "STUBaseWeapone.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapone : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapone();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MeshComponent;

protected:
    virtual void BeginPlay() override;
};
