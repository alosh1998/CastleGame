// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class LEARNINGPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;


	// using TSubclassOf: in the blueprint we will have a dropdown menu of classes that are subclasses of <Templat> 
	// in this case we will have menu that contains critter and critter_bp
	// this way we can assign a blueprint to a variable in c++ class, by choosing from the dropdown menu
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ACritter> PawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// BlueprintPure: means that this function will act as a getter in the blueprint
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetSpawnPoint();

	// this function have some blueprint functionality and some C++ functionality, so basically hybrid
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Spawning")
	void SpawnOurPawn(UClass* ToSpawn, const FVector& Location);

};
