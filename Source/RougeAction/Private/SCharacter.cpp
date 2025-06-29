// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->bUsePawnControlRotation = true; // 允许SpringArm根据Pawn的控制器旋转
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp); 

    GetCharacterMovement()->bOrientRotationToMovement = true; // 角色朝向移动方向


    InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

    bUseControllerRotationYaw = false; // 禁用角色的Yaw旋转控制
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0; // 忽略Pitch旋转
    ControlRot.Roll = 0; // 忽略Roll旋转
    AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0; // 忽略Pitch旋转
    ControlRot.Roll = 0; // 忽略Roll旋转

    // x -> Forward Red, y -> Right Green, Z -> Up Blue

    FVector RightVec = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVec, Value);
}

void ASCharacter::Jump()
{
    Super().Jump();
}

void ASCharacter::PrimaryAttack()
{
    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer( 
        TimerHandle_PrimaryAttack,
        this,
        &ASCharacter::PrimaryAttack_TimeElapsed,
        0.2f
    );

}

void ASCharacter::PrimaryInteract()
{
    //if (InteractionComp != nullptr)
    {
        InteractionComp->PrimaryInteract();
    }
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    // 还需要再编辑器，Project Settings -> Input 中添加 "MoveForward" 的轴映射
    PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
    PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
        &ACharacter::Jump);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
    FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


