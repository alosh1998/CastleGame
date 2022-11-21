// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// check to make sure everything is still valid and that we are allowed to move
	// check if there is owner for this pawn, check updated component defined previously, 
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get and clear the vector from collider
	// ConsumeInputVector will return value before setting vector to zero, the value was originally added by the AddInputVector in the collider.cpp
	// then clamped to 1 then multiply by delta time
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.f;

	if (!DesiredMovementThisFrame.IsNearlyZero()) 
	{

		FHitResult Hit;
		// third param is sweeping is for collision so set to true
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
	
		// if we bump into something slide along the side of it
		// IsValidBlockingHit() will return true if the pawn hit something and it is valid blocking hit, 
		if (Hit.IsValidBlockingHit()) {
			//if true we slide along it
			// SlideAlongSurface: as the pawn bump into something, the vector of it is stored in the normal vector and use it
			// in combination with the Desired direction the pawn is trying to go to, to calculate best direction for the pawn to go to if the pawn was to slide along side the surface 
			// 1 param: direction of movement
			// 2 param: hit time
			// 3 param: normal vector of the surface we hit
			// 4 param: the actuall hit result
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	
	}

}