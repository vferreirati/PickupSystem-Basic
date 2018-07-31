// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickup.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneCaptureComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComp);
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
	UE_LOG(LogTemp, Warning, TEXT("%s wants to pick me up!"), *AttachTo->GetName());
}

void ABasePickup::OnRelease() {
	// TODO: Detach from actor
}
