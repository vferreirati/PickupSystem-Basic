// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "HandController.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	if (HandControllerClass) {
		SpawnControllers();
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::SpawnControllers() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ControllerLeft = GetWorld()->SpawnActor<AHandController>(HandControllerClass, SpawnParams);
	ControllerLeft->AttachToComponent(RootComp, FAttachmentTransformRules::SnapToTargetIncludingScale);

	ControllerRight = GetWorld()->SpawnActor<AHandController>(HandControllerClass, SpawnParams);
	ControllerRight->AttachToComponent(RootComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
	ControllerRight->SetAsRightHand();
}