// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectile : public AActor
{
	GENERATED_BODY()

protected:
	
	// sphere ->size ,collision etc
	UPROPERTY(EditDefaultsOnly,Category="Components");
	TObjectPtr<USphereComponent> SphereComponent;
	
	//sphere-> speed,bounce back etc
	UPROPERTY(EditDefaultsOnly,Category="Components");
	TObjectPtr<UProjectileMovementComponent>ProjectileMovementComponent;
	
public:
	
	ARogueProjectile();
};
