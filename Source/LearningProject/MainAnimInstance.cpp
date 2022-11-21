// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "Main.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation() 
{
	if (Pawn == nullptr) {
		
		Pawn = TryGetPawnOwner();// return the pawn that owns the animation and assign it to Pawn
		if (Pawn)
		{
			Main = Cast<AMain>(Pawn);
		}
	}
}
// similar to tick()
void UMainAnimInstance::UpdateAnimationProperties() {
	if (Pawn == nullptr) 
	{
		Pawn = TryGetPawnOwner();// return the pawn that owns the animation and assign it to Pawn

	}
	if (Pawn) {
		// assign speed to how fast the pawn is going at that particular frame
		FVector Speed = Pawn->GetVelocity();

		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();// boolean will be either true or false based upon if the pawn has jumped or not

		if (Main == nullptr)
		{
			Main = Cast<AMain>(Pawn);
		}
	}
}