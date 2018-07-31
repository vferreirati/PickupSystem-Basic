// Fill out your copyright notice in the Description page of Project Settings.

#include "HandController.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"


// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	MotionControllerComp = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerComp"));
	MotionControllerComp->SetupAttachment(RootComp);

	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(MotionControllerComp);

	GrabSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GrabSphere"));
	GrabSphere->SetupAttachment(HandMesh);
}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandController::SetAsRightHand() {
	MotionControllerComp->SetTrackingSource(EControllerHand::Right);
	HandMesh->SetRelativeScale3D(FVector(1, 1, -1));
}