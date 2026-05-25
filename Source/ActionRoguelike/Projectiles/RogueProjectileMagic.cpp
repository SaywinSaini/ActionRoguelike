// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ARogueProjectileMagic::ARogueProjectileMagic()
{
 ProjectileMovementComponent->InitialSpeed = 2000.0f;	
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//keep the base implementation
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	FVector HitFromDirection = GetActorRotation().Vector();
	
	UGameplayStatics::ApplyPointDamage(OtherActor,10.0f,HitFromDirection,Hit,GetInstigatorController(),this,DmgTypeClass);
}
