#pragma once

#include <CoreMinimal.h>
#include <GameFramework/HUD.h>

#include "STUGameHUD.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void DrawHUD() override;

    void DrawCrossHair();
};
