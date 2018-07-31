// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

UCLASS()
class PICKUPSYSTEM_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandController();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetAsRightHand();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UMotionControllerComponent* MotionControllerComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* HandMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* GrabSphere;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
