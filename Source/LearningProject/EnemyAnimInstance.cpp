// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr) {

		Pawn = TryGetPawnOwner();// return the pawn that owns the animation and assign it to Pawn
		if (Pawn)
		{
			Enemy = Cast<AEnemy>(Pawn);
		}
	}
}
// similar to tick()
void UEnemyAnimInstance::UpdateAnimationProperties() {
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();// return the pawn that owns the animation and assign it to Pawn
		if (Pawn)
		{
			Enemy = Cast<AEnemy>(Pawn);
		}
	}
	
	if (Pawn)
	{
		// assign speed to how fast the pawn is going at that particular frame
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
	
}