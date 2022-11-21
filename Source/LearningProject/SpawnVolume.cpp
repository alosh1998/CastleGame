// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Critter.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// get a random point on the spawn and return it
FVector ASpawnVolume::GetSpawnPoint() 
{
	// get the dimensions of the box
	FVector Extent = SpawningBox->GetScaledBoxExtent();

	// the origin of the box
	FVector Origin = SpawningBox->GetComponentLocation();

	// this will generate a random point in the box
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

	return Point;

}
/** adding _Implementation to function name, tells UE that this is the implementation scripted out in c++, and that part of it 
will be in blueprint*/
void ASpawnVolume::SpawnOurPawn_Implementation(UClass* ToSpawn, const FVector& Location) {
	if (ToSpawn) // check if spawn isnt null
	{
		UWorld* World = GetWorld();// get the world
		FActorSpawnParameters SpawnParams;
		if (World) // check if world isnt null
		{
			// we are spawning an actor in the world using the paramters feed into the function
			// then store it inside CritterSpawned for further manipulation.
			ACritter* CritterSpawned = World->SpawnActor<ACritter>(ToSpawn, Location, FRotator(0.f), SpawnParams);
		}
	}
}
