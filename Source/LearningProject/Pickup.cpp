 // Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"

APickup::APickup()
{
	
}
void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		// cast OtherActor to AMain and store in Main
		AMain* Main = Cast<AMain>(OtherActor);
		// if main isnt null
		if (Main)
		{
			OnPickupBP(Main);
			/* 
			 removed so that the class could be used with potions as well
			 increment players coins when overlaping with coins
			 Main->IncrementCoin(CoinCount);
			 */

			//add pickup location to the array
			Main->PickupLocations.Add(GetActorLocation());
			// play particles
			if (OverlapParticles)
			{
				//Spawn a particle if not null
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true);
			}
			// play sound
			if (OverlapSound)
			{
				UGameplayStatics::PlaySound2D(this, OverlapSound);
			}

			// destroy the actor and everthing inside of the actor
			Destroy();

		}
	}
}

void APickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("APickup::Overlap End."));
}
