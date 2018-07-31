// Fill out your copyright notice in the Description page of Project Settings.

#include "HandController.h"
#include "BasePickup.h"
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
	GrabSphere->SetupAttachment(MotionControllerComp);
}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();
	HandState = EHandState::Open;
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandController::SetHand(EControllerHand Hand) {
	MotionControllerComp->SetTrackingSource(Hand);
	
	// Invert the hand if left.
	if (Hand == EControllerHand::Left) {
		HandMesh->SetRelativeScale3D(FVector(1, 1, -1));
	}	
}

void AHandController::OnGrab() {
	HandState = EHandState::Grab;
	UpdateHandState();

	// Get Nearest Object to GrabSphere
	AActor* NearestObject = GetNearestObject();

	if (NearestObject) {
		UE_LOG(LogTemp, Warning, TEXT("Nearest object is: %s"), *NearestObject->GetName())
	}

	// Check if it's a pickup actor
		// if so, pick it up
}

void AHandController::OnRelease() {
	HandState = EHandState::Open;
	UpdateHandState();
}

AActor* AHandController::GetNearestObject() {
	TArray<AActor*> Actors;
	GrabSphere->GetOverlappingActors(Actors, ABasePickup::StaticClass());

	AActor* NearestActor = nullptr;
	float MinorDistance = 50000.f;
	FVector GrabSphereLocation = GrabSphere->GetComponentLocation();
	for (AActor* Actor : Actors) {
		FVector ActorLocation = Actor->GetActorLocation();
		float CurrentDistance = (GrabSphereLocation - ActorLocation).Size();
		if (CurrentDistance < MinorDistance) {
			NearestActor = Actor;
			MinorDistance = CurrentDistance;
		}
	}

	return NearestActor;
}