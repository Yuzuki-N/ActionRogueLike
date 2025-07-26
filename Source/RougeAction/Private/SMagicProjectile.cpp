// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    // 从编辑器创建了Projectile的碰撞预设
    SphereComp->SetCollisionProfileName("Projectile");
    // 这里绑定了一个动态事件，当SphereComp与其他Actor发生重叠时会调用OnActorOverlap函数
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
    RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(RootComponent);

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
    MovementComp->InitialSpeed = 1000.0f;
    MovementComp->bRotationFollowsVelocity = true; // 使投射物的旋转跟随其速度方向
    MovementComp->bInitialVelocityInLocalSpace = true;


}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
    Super::BeginPlay();

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  
{  
    if (OtherActor && OtherActor != GetInstigator())  
    {  
        USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));  

        if (AttributeComp)  
        {  
            AttributeComp->ApplyHealthChange(-20.0f);  
            Destroy(); // 销毁投射物  
        }  
    }  
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

