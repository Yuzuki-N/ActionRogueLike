// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2000.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	ForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, 
		TEXT("OnActorHit reached, %s, at time %f"), *(GetNameSafe(OtherActor) + TEXT("Fuck Macro!")),
		GetWorld()->TimeSeconds);


	FString CombinedString = FString::Printf(TEXT("Hit location at: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, "hit", NULL, FColor::Red, 2.0f, true, 1.5f);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

