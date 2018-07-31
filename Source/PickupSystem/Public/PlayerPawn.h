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

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
