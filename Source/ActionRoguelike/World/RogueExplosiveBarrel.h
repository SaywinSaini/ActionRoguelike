// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class URadialForceComponent;
class USoundBase;
class UStaticMeshComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditDefaultsOnly,Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly,Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
    
	UPROPERTY(EditDefaultsOnly,Category="Effects")
	TObjectPtr<UNiagaraSystem> ParticleEffect;
	
	//flame sound
	UPROPERTY(EditDefaultsOnly,Category="Sound");
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	//explosion
	UPROPERTY(EditDefaultsOnly,Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UFUNCTION(BlueprintCallable)
	void Explode();
	
	void ParticleTimer();
	bool bExploded = false;
	UNiagaraComponent* ParticleComponent;
	FTimerHandle ExplosionTimerHandle;
	
public:
	
	ARogueExplosiveBarrel();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    private:
	
};
