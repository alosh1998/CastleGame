// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	// UMETA: tomark enum constants
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_Dead UMETA(DisplayName = "Dead"),
	// the last one is for default
	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),
	ESS_MAX UMETA(DisplayName = "DefaultMAX")
};


UCLASS()
class LEARNINGPROJECT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	// what kind of particles the main character will play when hit, eg blood squirting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class  UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class USoundCue* HitSound;

	// can be used to store locations 
	TArray<FVector> PickupLocations;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UFUNCTION(BlueprintCallable)
		void ShowPickupLcoations();
//////////////////////////////////// player movement 
	// setter for movementStatus and running speed
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	/** press down to enable sprinting*/
	void ShiftKeyDown();

	/**release to stop sprinting*/
	void ShiftKeyUp();

////////////////////////////////////////// player stamina

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EStaminaStatus StaminaStatus;

		FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float StaminaDrainRate;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MinSprintStamina;

		// player interpolating to aim at enemy when close enough

		float InterpSpeed;
		bool bInterpToEnemy;
		void SetInterpToEnemy(bool Interp);

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		class AEnemy* CombatTarget;

		FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

		FRotator GetLookAtRotationYaw(FVector Target);


	/** 
	Camera boom positiong the camera behind the player
	use meta = (AllowPrivateAccess="true"), to make the variable only accessible by the BP related to this class and not by other blueprint
	*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rates to scale turning functions for camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/**
	/*
	/*
	/*Player stats
	/*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Player stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Player stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	int32 Coins;


	void DecrementHealth(float Amount);

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator,AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void IncrementCoin(int32 Amount);
	UFUNCTION(BlueprintCallable)
	void IncrementHealth(float Amount);

	void Die();

	virtual void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// called for forward/backward movement
	void MoveForward(float Value);

	// called for righ and left movement
	void MoveRight(float Value);

	// boolean to control players movement and prevent from sprinting while in idle position
	bool bMovingForward;
	bool bMovingRight;

	/** called via input to turn at a given rate 
	*@param Rate This is a normalized rate. eg 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);


	/** called via input to look up/down at a given rate 
	*@param Rate This is a normalized rate. eg 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	bool bLMBDown;

	void LMBDown();
	void LMBUp();

	// Using forceinline the program doesnt have to jump into this file to lookup for the definition of this function
	// setting up setters and getters
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AWeapon* EquipedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverLappingItem;

	//setters
	void SetEquippedWeapon(AWeapon* WeaponToSet);
	
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquipedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverLappingItem = Item; }

	// character attacking system
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
		class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	void UpdateCombatTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<AEnemy> EnemyFilter;

};
