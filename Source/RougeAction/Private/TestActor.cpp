// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include "SAttributeComponent.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
    AttributeComp->OnHealthChanged.AddDynamic(this, &ATestActor::OnHealthChanged);
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestActor::OnHealthChanged(AActor* Inst, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Delta: %d"), Delta);
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

