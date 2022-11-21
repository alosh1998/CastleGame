// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGPROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	// similar to beginPlay()
	virtual void NativeInitializeAnimation() override;


	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();




	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category="Movement")
	float MovementSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	class APawn* Pawn;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	class AMain* Main;

	
};
