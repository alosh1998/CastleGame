// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class LEARNINGPROJECT_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	// this is similar to capsule used for the player earlier
	/** Overlap volume for the functionality to be triggered*/
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Floor Switch")
	class UBoxComponent* TriggerBox;
	/**Switch for the character to step on*/
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Floor Switch")
	class UStaticMeshComponent* FloorSwitch;
	/** Door to move when the floor switch is stepped on*/
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Floor Switch")
	UStaticMeshComponent* Door;

	/**initial location for the door*/
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialDoorLocation;

	/**initial location for the floor switch*/
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialSwitchLocation;

	FTimerHandle SwitchHandle;
	// function to delay closing door
	void CloseDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	float SwitchTime;

	bool bCharacterOnSwitch;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// when binding a function to OnComponentBeginOverlap, it must be UFUNCTION() 
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// BlueprintImplementableEvent: means that you dont have to implement the functionality of the function in C++...
	// ...it can be done in blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void RaiseDoor();


	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void LowerDoor();


	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void RaiseFloorSwitch();


	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void LowerFloorSwitch();

	// BlueprintCallable: means that it can be called from blueprint but the implementation will be in C++
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateDoorLocation(float Z);

	// BlueprintCallable: means that it can be called from blueprint but the implementation will be in C++
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
		void UpdateFloorSwitchLocation(float Z);
};
