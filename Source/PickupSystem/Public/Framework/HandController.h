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

	class ABasePickup* CurrentObject;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "HandController")
	void UpdateHandState();

	AActor* GetNearestObject();
};
