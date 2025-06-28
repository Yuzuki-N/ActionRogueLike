// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USInteractionComponent::PrimaryInteract()
{
	FHitResult HitRes;
	AActor* MyOwner = GetOwner();

	FVector MyLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(MyLocation, EyeRotation);
    FVector End = MyLocation + (EyeRotation.Vector() * 1000);

    FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(HitRes, MyLocation, End, ObjectQueryParams);
	
	AActor* HitActor = HitRes.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<USGameInterface>())
		{
            APawn* MyPawn = Cast<APawn>(MyOwner);
			// hitActor是调用者, MyPawn是函数的参数
            ISGameInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

