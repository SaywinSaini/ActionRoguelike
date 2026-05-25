
#include "RogueProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(RootComponent);
	
	RadialForceComponent->ForceStrength = -800000.0f;
	RadialForceComponent->Radius = 1200.0f;
	
	//Avoid sucking playr into the blackhole
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	// suck up nearby objects, small enough to let them miss the sphere and flail around a bit first
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");
	
	ProjectileMovementComponent->InitialSpeed= 500.0f;
	
	InitialLifeSpan = 5.0f;
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ARogueProjectileBlackhole::OnSphereOverlappedActor);
	
}

void ARogueProjectileBlackhole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics()){
		OtherActor->Destroy();
	}
}


