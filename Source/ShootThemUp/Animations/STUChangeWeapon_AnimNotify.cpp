// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/STUChangeWeapon_AnimNotify.h"
#include "STUChangeWeapon_AnimNotify.h"

void USTUChangeWeapon_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    OnAnimNotifyDelegate.Broadcast(MeshComp, Animation);
}
