// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class LEARNINGPROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();



	// creating static mesh using cpp
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponensts")
	UStaticMeshComponent* StaticMesh;

	// Location used by setActorLocation when BeginPlay() is called
	// EditInstanceOnly will make sure that only instance of this actor are editable, default actor cannot be edited.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
		FVector InitialLocation;

	// VisibleInstanceOnly will make the property only visible
	// Location of the actor when dragged in from the editor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector PlacedLocation;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Floater Variables")
		FVector WorldOrigin;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Floater Variables")
		FVector InitialDirection;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Floater Variables")
		bool bShouldFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	bool bInitializeFloaterLocations;

	// contains vector for the force to be applied to the object
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector initalForce;

	// contains vector for the Torque to be applied to the object
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
		FVector initalTorque;

private:
	float RunningTime;

	UPROPERTY(EditAnyWhere, Category = "FloaterVariables | Wave Parameter ")
	float Amplitude;

	UPROPERTY(EditAnyWhere, Category = "FloaterVariables | Wave Parameter ")
	float TimeStrech;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
