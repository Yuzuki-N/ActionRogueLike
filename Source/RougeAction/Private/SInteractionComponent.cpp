// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameInterface.h"
#include "DrawDebugHelpers.h"
#include "CollisionShape.h"

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

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
    FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

    FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//bool bHitBlock = GetWorld()->LineTraceSingleByObjectType(HitRes, EyeLocation, End, ObjectQueryParams);


	float Radius = 20.0f;
	FCollisionShape Shape;
    Shape.SetSphere(Radius); // 设置碰撞形状为半径为20的球体

	TArray<FHitResult> Hits;
	bool bHitBlock = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, 
		FQuat::Identity, ObjectQueryParams, Shape);

	FColor HitColor = bHitBlock ? FColor::Green : FColor::Red;

	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<USGameInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				// hitActor是调用者, MyPawn是函数的参数
				ISGameInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
        DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 12, HitColor, false, 2.0f);
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, HitColor, false, 2.0f, 0, 0);
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

