#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "STUTestDamager.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUTestDamager : public AActor
{
    GENERATED_BODY()

public:
    ASTUTestDamager();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damager")
    float Radius = 250.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damager")
    float Damage = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damager")
    FColor Color = FColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damager")
    bool DoFullDamage = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damager")
    TSubclassOf<UDamageType> DamageClass;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
