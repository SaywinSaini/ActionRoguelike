#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileTeleport.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectileTeleport : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	
	FTimerHandle TeleportHandle;
	
	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	float DetonateDelay = 2.0f;
	
	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	float TeleportSecondaryDelay = 0.2f;
	
	void StartDelayedTeleport();
	
	void HandleTeleportation();
	
	virtual void BeginPlay() override;
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	
public:

	ARogueProjectileTeleport();
};
