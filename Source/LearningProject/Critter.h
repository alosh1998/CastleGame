// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Critter.generated.h"

UCLASS()
class LEARNINGPROJECT_API ACritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACritter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// declaring static mesh component
	// by adding the keyword class, you telling VS that this will defined in the .cpp file
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* MeshComponent;

	// declaring camera component that will be following the paws/user
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	// the speed at which the pawn will move
	UPROPERTY(EditAnywhere, Category = "Pawn Movement")
	float MaxSpeed;

private:
	// setting functions for movement of the pawn
	void MoveForward(float Value);

	void MoveRight(float Value);


	FVector CurrentVelocity;


};
