// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickup.h"
#include "HandController.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::OnPickup(USceneComponent* AttachTo) {
	BaseMesh->SetSimulatePhysics(false);
	AttachToComponent(AttachTo, FAttachmentTransformRules::KeepWorldTransform);	
}

void ABasePickup::OnRelease() {
	BaseMesh->SetSimulatePhysics(true);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);	
}