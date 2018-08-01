// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class PICKUPSYSTEM_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPickup(class USceneComponent* AttachTo);

	virtual void OnRelease();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
