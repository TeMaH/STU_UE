// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "STUChangeWeapon_AnimNotify.generated.h"

/**
 *
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimNotifySignature, USkeletalMeshComponent*, UAnimSequenceBase*);

UCLASS()
class SHOOTTHEMUP_API USTUChangeWeapon_AnimNotify : public UAnimNotify
{
    GENERATED_BODY()
public:
    FOnAnimNotifySignature OnAnimNotifyDelegate;

protected:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
