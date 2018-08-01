// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

UENUM(BlueprintType)
enum class EHandState : uint8 {
	Open,
	CanGrab,
	Grab
};

UCLASS()
class PICKUPSYSTEM_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnGrab();

	void OnRelease();

	void SetHand(EControllerHand Hand);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UMotionControllerComponent* MotionControllerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* HandMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* GrabSphere;

	UPROPERTY(BlueprintReadOnly, Category = "HandController")
	EHandState HandState;

	// Current Object reference being held by this actor
	class ABasePickup* CurrentObject;

	// Is the player pressing the grip button?
	bool bWantsToGrab;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Checks and sets the correct hand state
	void UpdateHandState();

	// Updates the hand state on AnimationBlueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "HandController")
	void UpdateHandAnimState();

	// Gets the nearest ABasePickup Actor to GrabSphere
	AActor* GetNearestObject();
};
