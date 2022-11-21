// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class LEARNINGPROJECT_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	// define shpere for the collision and the physics
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;

	// declaring camera component that will be following the paws/user
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	// this helps controll camera motion
	class USpringArmComponent* SpringArm;

	// this variable is a reference to the movement class we have created becasue pawn doesnt have default movement
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UColliderMovementComponent* OurMovementComponent;

	// this acts as a getter for the OurMovementComponent
	// because the pawn already has it we need to overcome it.
	// when function is declared as const it means that the function can't change data members
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	/////////////////////////////////////////////// define setters and getters////////////////////////////////////////////////////////

	// Using forceinline the program doesnt have to jump into this file to lookup for the definition of this function
	// everywhere the function is called the definition will be pasted along, therefore making it faster
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh) {  MeshComponent = Mesh; }
	FORCEINLINE USphereComponent* GetShpereComponent() { return SphereComponent; }
	FORCEINLINE void SetShpereComponent(USphereComponent* Shpere) { SphereComponent = Shpere; }

	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* InCamera) { Camera = InCamera; }
	FORCEINLINE USpringArmComponent* GetSpringComponent() { return SpringArm; }
	FORCEINLINE void SetSpringComponent(USpringArmComponent* InSpringArm) { SpringArm = InSpringArm; }


private:
	void MoveForward(float input);
	void MoveRight(float input);

	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

	// this will store axis values, to store the values of the user mouse input
	// will be used inside pitch and yaw camera 
	FVector2D CameraInput;

};
