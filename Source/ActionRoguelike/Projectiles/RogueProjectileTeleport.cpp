#include "RogueProjectileTeleport.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();

	// If projectile never hits anything,
	// teleport automatically after travel time
	GetWorldTimerManager().SetTimer(
		TeleportHandle,
		this,
		&ThisClass::StartDelayedTeleport,
		DetonateDelay,
		false
	);
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Prevent double teleport
	if (!GetActorEnableCollision())
	{
		return;
	}

	// Stop the automatic travel timer
	GetWorldTimerManager().ClearTimer(TeleportHandle);

	StartDelayedTeleport();
}

void ARogueProjectileTeleport::StartDelayedTeleport()
{
	// Prevent running twice
	if (!GetActorEnableCollision())
	{
		return;
	}

	PlayExplodeEffect();

	ProjectileMovementComponent->StopMovementImmediately();

	LoopedNiagaraComponent->Deactivate();

	// Stop sound
	LoopedAudioComponent->Stop();

	SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(
		TeleportHandle,
		this,
		&ThisClass::HandleTeleportation,
		TeleportSecondaryDelay,
		false
	);
}

void ARogueProjectileTeleport::HandleTeleportation()
{
	APawn* ActorToTeleport = GetInstigator();

	check(ActorToTeleport);

	// Slight offset upward to avoid clipping into ground
	FVector TeleportLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);

	ActorToTeleport->TeleportTo(
		TeleportLocation,
		ActorToTeleport->GetActorRotation()
	);

	Destroy();
}