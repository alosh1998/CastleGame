// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Sound/SoundCue.h"
#include "Enemy.h"
#include "MainPlayerController.h"


// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera boom (pulls toward the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 400.f; // camera follows at this distance
	CameraBoom->bUsePawnControlRotation = true; // rotate arm based on controller
	// set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(48.f, 115.f);

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // we dont want the camera to follow along with the controller rotation instead it follows the spring arm which already follows controller

	// Set our turn rates for input
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// dont rotate when the controller rotates
	// to avoid the character from moving while the camera is moving, set the following values to false
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// configure character movement
	// setting this value to true will make the character face towards the direction it is physically moving to
	GetCharacterMovement()->bOrientRotationToMovement = true;// character moves in the direction of input...
	// we only change the value of yaw to 540.f and set the others to 0 because we dont want the character to move up/down or roll, only the yaw movement
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);// ... at this rotation rate
	// how long the character can jump
	GetCharacterMovement()->JumpZVelocity = 650.f;
	//when the player is in the air, AirControl allows the ability to move the character whilst in the air
	GetCharacterMovement()->AirControl = 0.2f;

	MaxHealth = 100.f;
	Health = 65.f;
	MaxStamina = 150.f;
	Stamina = 120.f;
	Coins = 0;
	RunningSpeed = 650.f;
	SprintingSpeed = 950.f;
	bShiftKeyDown = false;
	bLMBDown = false;

	// init enums
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;

	StaminaDrainRate = 25.f;
	MinSprintStamina = 50.f;

	InterpSpeed = 15.f;
	bInterpToEnemy = false;

	bHasCombatTarget = false;

	bMovingForward = false;
	bMovingRight = false;

}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(GetController());
	// limit pitch of camera
	APlayerCameraManager* const cam_manager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	cam_manager->ViewPitchMin = -50.0f;
	cam_manager->ViewPitchMax = 10.0f;

	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if character is dead then exit the function without doing the rest of the functionalities
	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	float DeltaStamina = StaminaDrainRate * DeltaTime;

	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		// check if key is down
		if (bShiftKeyDown)
		{
			// check if stamina level is below min state
			if (Stamina - DeltaStamina <= MinSprintStamina)
			{
				//set status to below min
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				Stamina -= DeltaStamina;
			}
			// if level isnt below min state
			else
			{
				Stamina -= DeltaStamina;
			}

			// set character movement to sprinting if if player is moving otherwise set to normal
			if (bMovingForward || bMovingRight)
			{
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
			else
			{
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}

		}
		else // shift key up
		{

			// if stamina level is greater than the max, then stop incrementing stamina
			if (Stamina + DeltaStamina >= MaxStamina)
			{
				Stamina = MaxStamina;

			}
			else// if stamina levelis isnt greater or equal to max, incrementing stamina
			{
				Stamina += DeltaStamina;
			}
			// set character movement to normal while key is down
			SetMovementStatus(EMovementStatus::EMS_Normal);

		}

		break;
	case EStaminaStatus::ESS_BelowMinimum:

		if (bShiftKeyDown) // key up
		{
			// if stamina level is less or equal to 0
			if (Stamina - DeltaStamina <= 0.f)
			{
				//set status to below exhausted
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0; // make stamina 0
				// set movement to normal so the player can't sprint
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else // if stamina level isnt zero this means that it is in below minum level
			{
				// decrement stamina level
				Stamina -= DeltaStamina;
				// set movement to Sprinting because the level isnt below min yet
				// set character movement to sprinting if player is moving otherwise set to normal
				if (bMovingForward || bMovingRight)
				{
					SetMovementStatus(EMovementStatus::EMS_Sprinting);
				}
				else
				{
					SetMovementStatus(EMovementStatus::EMS_Normal);
				}
			}

		}
		else //  key down
		{
			// if the stamina level is greater than min sprint value
			if (Stamina + DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				// increment stamina level
				Stamina += DeltaStamina;
			}
			else 
			{
				// increment stamina level
				Stamina += DeltaStamina;
			}
			// set movement to Noraml because the level is below min still
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}

		break;
	case EStaminaStatus::ESS_Exhausted:
		if (bShiftKeyDown)// if key down
		{
			// set the stamina value back to 0
			Stamina = 0.f;
		}
		else // key up
		{
			// switch to exhausted recovering
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			// increment stamina level
			Stamina += DeltaStamina;
		}
		// set movement to Normal because the level is below min still
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		// if the level is above the min 
		if (Stamina + DeltaStamina >= MinSprintStamina)
		{
			// set stamina to true
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			// increment stamina level
			Stamina += DeltaStamina;
		}
		else
		{
			// increment stamina level
			Stamina += DeltaStamina;
		}
		// set movement to Normal because the level is below min still
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	default:
		;//empty statement
	}

	if (bInterpToEnemy && CombatTarget)
	{
		// get the yaw rotation of the enemy
		FRotator LookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());

		// interp the actor in to the desired rotation smoothly

		FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);
		SetActorRotation(InterpRotation);
	}

	// if there is a target
	if (CombatTarget)
	{
		// get the target location
		CombatTargetLocation = CombatTarget->GetActorLocation();

		if (MainPlayerController)
		{
			// update the location the enemy in the main player controller using the combat target with the range of the player
			MainPlayerController->EnemyLocation = CombatTargetLocation;
		}
	}

}
// orient the player to face the enemy during combat
FRotator AMain::GetLookAtRotationYaw(FVector Target)
{

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);
	return LookAtRotationYaw;
}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// check() will check if the value is true and if not it will stop the code
	check(PlayerInputComponent);
	// use IE_Pressed for when the key is pressed 
	// bindAction unlike bindAxis, doesnt send value every frame 
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &AMain::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// user input for equipping and unequipping 
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMain::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMain::LMBUp);


	// movement status action binding
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMain::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMain::ShiftKeyUp);

	// character movement axis binding
	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);

	// character rotating
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpAtRate);

}

void AMain::MoveForward(float Value) 
{
	bMovingForward = false;

	if ((Controller != nullptr) && (Value != 0.f) && (!bAttacking) && (MovementStatus != EMovementStatus::EMS_Dead))
	{
		// find which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// after finding which way is forward, use matrix function to get the X axis of the rotation
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement into the character based on the direction we passed
		AddMovementInput(Direction, Value);

		bMovingForward = true;
	}
}

// called for righ and left movement
void AMain::MoveRight(float Value) 
{
	bMovingRight = false;
	if ((Controller != nullptr) && (Value != 0.f) && (!bAttacking) && (MovementStatus != EMovementStatus::EMS_Dead))
	{
		// find which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// after finding which way is forward, use matrix function to get the X axis of the rotation
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement into the character based on the direction we passed
		AddMovementInput(Direction, Value);

		bMovingRight = true;
	}

}

void AMain::TurnAtRate(float Rate) {
	// this functions take value and rotate the controller in the yaw direction according to the value
	// Rate will be either 1 or 0, BaseTurnRate already defined, GetDeltaSeconds to get the delta time outside tick()
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void AMain::LookUpAtRate(float Rate) {
// this functions take value and rotate the controller in the yaw direction according to the value
// Rate will be either 1 or 0, BaseTurnRate already defined, GetDeltaSeconds to get the delta time outside tick()
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LMBDown()
{
	bLMBDown = true;

	// if character is dead then exit the function without doing the rest of the functionalities
	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	// check if character is overlapping with an item
	if (ActiveOverLappingItem)
	{
		// if overlapped with weapon 
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverLappingItem);
		if (Weapon)// check weapon isnt null
		{
			// equip the character
			Weapon->Equip(this);
			// set to null to allow overlapping with other items
			SetActiveOverlappingItem(nullptr);
		}
	}
	else if(EquipedWeapon)
	{
		// if weapon is already equipped
		Attack();
	}
}

void AMain::LMBUp()
{
	bLMBDown = false;
}

// decrement players health when overlaping with explosives
void AMain::DecrementHealth(float Amount)
{
	if (Health - Amount <= 0.f) 
	{
		// update health bar
		Health -= Amount;
		
		Die();
	}
	else {
		// update health bar
		Health -= Amount;
	}
}
// increment players coin when overlaping with coins
void AMain::IncrementCoin(int32 Amount)
{
	Coins += Amount;
}

void AMain::IncrementHealth(float Amount)
{
	if (Health + Amount >= MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health += Amount;
	}
}

// called when characters health is zero
void AMain::Die() 
{

	if (MovementStatus == EMovementStatus::EMS_Dead) return;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage)
	{
		// play death animation
		AnimInstance->Montage_Play(CombatMontage, 1.0f);
		AnimInstance->Montage_JumpToSection(FName("Death"), CombatMontage);

	}
	// set movement status to death to prevent character from moving after it dies.
	SetMovementStatus(EMovementStatus::EMS_Dead); 
}

void AMain::Jump(){
	// stop jump animation when character is dead
	if (MovementStatus != EMovementStatus::EMS_Dead)
	{
		ACharacter::Jump();
	}
}

void AMain::DeathEnd()
{
	// stop animating the character
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;

}

// this function will take care of setting the movement status and changing the speed based on the status of the player
void AMain::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;

	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}
/** press down to enable sprinting*/
void AMain::ShiftKeyDown()
{
	bShiftKeyDown = true;
}

/**release to stop sprinting*/
void AMain::ShiftKeyUp()
{
	bShiftKeyDown = false;
}

void AMain::ShowPickupLcoations()
{
	
	// show spheres over places the player picked coins from
	// auto will automatically detect the type of the required variable, in this case FVector
	for (auto Location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Green, 10.f, .5f);

	}


}

void AMain::SetEquippedWeapon(AWeapon* WeaponToSet)
{
	// if already equipped a weapon destroy it
	if (EquipedWeapon)
	{
		EquipedWeapon->Destroy();
	}
	// equip a new weapon
	 EquipedWeapon = WeaponToSet; 
}

// characters attacking animation
void AMain::Attack()
{
	// check if the character isnt already attacking before issuing the attack, and the character isn't dead
	if (!bAttacking && MovementStatus != EMovementStatus::EMS_Dead)
	{
		bAttacking = true;
		SetInterpToEnemy(true); // when attacking set interpToEnemy to true using the setter to make the player face the enemy 
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage)
		{
			//randmize attacking animations
			int32 Section = FMath::RandRange(0, 1);
			switch (Section)
			{
			case 0:
				AnimInstance->Montage_Play(CombatMontage, 2.2f);
				AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
				break;
			case 1:
				AnimInstance->Montage_Play(CombatMontage, 1.8);
				AnimInstance->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
				break;
			default:
				;
			}
			
		}
	}
	

}

// called after the attack is finished
void AMain::AttackEnd()
{
	bAttacking = false;
	SetInterpToEnemy(false); // when attack end, set to false to prevent player from orienting with the enemy when not attacking

	// after attack is finish, check if key is pressed, and if so attack again
	if (bLMBDown)
	{
		Attack();
	}
}

void AMain::PlaySwingSound()
{
	if (EquipedWeapon->SwingSound)
	{
		UGameplayStatics::PlaySound2D(this, EquipedWeapon->SwingSound);
	}

}

void AMain::SetInterpToEnemy(bool Interp)
{
	bInterpToEnemy = Interp;
}

float AMain::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		// update health bar
		Health -= DamageAmount;

		Die();
		if (DamageCauser)
		{
			// to prevent the enemy from attacking main character after it dies.
			AEnemy* Enemy = Cast<AEnemy>(DamageCauser); // cast to enemy
			if (Enemy)
			{
				Enemy->bHasValidTarget = false;
			}
		}
	}
	else {
		// update health bar
		Health -= DamageAmount;
	}

	return DamageAmount;
}
// 
void AMain::UpdateCombatTarget()
{
	// overlapping actors array
	TArray<AActor*> OverlappingActors;
	// returns all overlapping actors
	GetOverlappingActors(OverlappingActors, EnemyFilter);

	if (OverlappingActors.Num() == 0)
	{
		// if no enemy remove any enemy healthbar
		if (MainPlayerController)
		{
			MainPlayerController->RemoveEnemyHealthBar();
		}
		return;
	}
	AEnemy* ClosestEnemy = Cast<AEnemy>(OverlappingActors[0]);

	// identify the closest enemy to the player
	if (ClosestEnemy)
	{
		FVector Location = GetActorLocation();
		float MinDist = (ClosestEnemy->GetActorLocation() - Location).Size();
		
		for (auto Actor : OverlappingActors)
		{
			AEnemy* Enemy = Cast<AEnemy>(Actor);

			if (Enemy)
			{
				float DistanceToActor = (Enemy->GetActorLocation() - Location).Size();
				if (DistanceToActor < MinDist)
				{
					MinDist = DistanceToActor;
					ClosestEnemy = Enemy;
				}
			}
		}
		// display enemy healthbar
		if (MainPlayerController)
		{
			MainPlayerController->DisplayEnemyHealthBar();

		}
		// set player target combat to the closest enemy
		SetCombatTarget(ClosestEnemy);
		bHasCombatTarget = true;
	}


}
