// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
	RootComponent = StaticMeshComponent;
	
	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComponent"));
	LoopedAudioComponent->SetupAttachment(StaticMeshComponent);
	LoopedAudioComponent->bAutoActivate = false;
	
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	// Must be quite large, depends on the Mass of the Actors we intend to launch such as the Cubes
	RadialForceComponent->ImpulseStrength = 150000.0f;
	RadialForceComponent->Radius = 750.f;
	// We don't need to Activate this component, that is only good for applying a constant radial force and not our desired one frame Impulse
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
}



float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	// Allow exploding once, also skip when timer is already running
	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return ActualDamage;
	}
	
	ParticleTimer();
	LoopedAudioComponent->Play(); 
	
	const float ExplosiveDealy = 3.0f;
	//Timer
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle,this, &ARogueExplosiveBarrel::Explode,ExplosiveDealy,false);
	
	return ActualDamage;
}
void ARogueExplosiveBarrel::Explode()
{
	bExploded = true;
	
	if (ParticleComponent)
	{
		ParticleComponent->DestroyComponent();
		ParticleComponent=nullptr;
	}
	if (LoopedAudioComponent)
	{
		LoopedAudioComponent->Stop();
	}
	RadialForceComponent->FireImpulse();
	
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this , ExplosionEffect,GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this,ExplosionSound,GetActorLocation(),FRotator::ZeroRotator);
	Destroy();
}

void ARogueExplosiveBarrel::ParticleTimer()
{
	ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(ParticleEffect, StaticMeshComponent, NAME_None,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
}






