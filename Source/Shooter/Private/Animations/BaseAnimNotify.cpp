// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/BaseAnimNotify.h"


void UBaseAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotify.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
