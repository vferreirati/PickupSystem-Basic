// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class PICKUPSYSTEM_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AHandController> HandControllerClass;

	class AHandController* ControllerLeft;
	class AHandController* ControllerRight;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawns both left and right controllers and attach to root component
	void SpawnControllers();
	
	// Grab input functions
	void GrabLeft();
	void ReleaseLeft();
	void GrabRight();
	void ReleaseRight();
};
