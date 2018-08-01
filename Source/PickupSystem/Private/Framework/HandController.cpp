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
	bWantsToGrab = false;
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateHandState();
	UpdateHandAnimState();	
}

void AHandController::SetHand(EControllerHand Hand) {
	MotionControllerComp->SetTrackingSource(Hand);
	
	// Invert the hand if left.
	if (Hand == EControllerHand::Left) {
		HandMesh->SetRelativeScale3D(FVector(1, 1, -1));
	}	
}

void AHandController::OnGrab() {
	bWantsToGrab = true;

	// Get Nearest Object to GrabSphere
	AActor* NearestObject = GetNearestObject();

	// Check if it's a pickup actor
	// if so, pick it up
	if (ABasePickup* Pickup = Cast<ABasePickup>(NearestObject)) {
		Pickup->OnPickup(MotionControllerComp);
		CurrentObject = Pickup;
	}	
}

void AHandController::OnRelease() {
	bWantsToGrab = false;

	// If we have a grabbed object and this object is grabbed by us
	if (CurrentObject && CurrentObject->GetRootComponent()->GetAttachParent() == MotionControllerComp) {
		CurrentObject->OnRelease();
	}	

	CurrentObject = nullptr;
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

void AHandController::UpdateHandState() {
	// Set to grab if we're holding something
	// Or the grip button is pressed
	if (CurrentObject || bWantsToGrab) {
		HandState = EHandState::Grab;
		
		// Else, if there's a grabbable object near hand
		// set to CanGrab
	} else if(AActor* NearestObject = GetNearestObject()) {
		HandState = EHandState::CanGrab;
	} else {
		HandState = EHandState::Open;
	}
}