// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
    Health = 100.0f; // Default health value
}


// Called when the game starts
bool USAttributeComponent::ApplyHealthChange(float Delta)
{
    Health += Delta;

    //OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
    // 上面的代码会报错，InstigatorActor设置为nullptr会错误，遇到这种问题不知道要怎么排查，ue直接闪退了
    OnHealthChanged.Broadcast(GetOwner(), this, Health, Delta);
    return true;
}

