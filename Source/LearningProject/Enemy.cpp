// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "Main.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "MainPlayerController.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	// ignore world dynamics such as explosives 
	AgroSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	AgroSphere->InitSphereRadius(600.f);

	CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	CombatSphere->SetupAttachment(GetRootComponent());
	CombatSphere->InitSphereRadius(100.f);

	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision"));
	// attach component to another component, in this case UBox to socket
	CombatCollision->SetupAttachment(GetMesh(), FName("EnemySocket"));
	/*
	when calling attachment function from within the constructor it is better if we call SetupAttachment instead of Attachment component,
	like the one below, this one we call when outside the constructor
	CombatCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("EnemySocket"));
	*/

	bOverlappingCombatSphere = false;

	Health = 75.f;
	MaxHealth = 100.f;
	Damage = 10.f;

	AttackMinTime = 0.5f;
	AttackMaxTime = 3.5f;

	EnemyMovementStatus = EEnemyMovmentStatus::EMS_Idle;

	DeathDelay = 3.f;

	bHasValidTarget = false;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController()); // cast b/c GetController() will return AController, and we are want AAIContorller
	// bind overlap events to overlap components
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AgroSphereOnOverlapEnd);

	CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::CombatSphereOnOverlapBegin);
	CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::CombatSphereOnOverlapEnd);

	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::CombatOnOverlapBegin);
	CombatCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemy::CombatOnOverlapEnd);


	// set collison to null by default
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	// ignore collision with all 
	CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// set to collide and overlap with only pawns
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// to avoid camera zooming in ignore camera
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);



}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Alive())
	{
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			MoveToTarget(Main);
		}
	}
}

void AEnemy::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		// when user is outside enemy agro zone, enemy will stop chasing
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			bHasValidTarget = false;
			// destroy only this instance of the enemy
			if (Main->CombatTarget == this)
			{
				Main->SetCombatTarget(nullptr);
			}

			Main->SetHasCombatTarget(false);
			// as soon as the player isnt within the sphere, remove enemy health bar
			Main->UpdateCombatTarget();

			// stop movement
			SetEnemyMovementStatus(EEnemyMovmentStatus::EMS_Idle);
			if (AIController)
			{
				AIController->StopMovement();
			}
			
		}
	}
 }

void AEnemy::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if (OtherActor && Alive())
	{
		// when the player is in the range of the enemy,
		// enemy starts attacking
		AMain* Main = Cast<AMain>(OtherActor);
		{
			if (Main)
			{
				bHasValidTarget = true;
				// set the combat target for the player
				Main->SetCombatTarget(this);
				Main->SetHasCombatTarget(true);

				// as soon as the player overlap with the combat sphere, display enemy health bar and update targets
				Main->UpdateCombatTarget();

				CombatTarget = Main;
				bOverlappingCombatSphere = true;
				// delay enemy attack, 
				float AttackTime = FMath::FRandRange(AttackMinTime, AttackMaxTime);
				GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);
			}
		}
		
	}
 }

void AEnemy::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherComp)
	{
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
		
			bOverlappingCombatSphere = false;
			MoveToTarget(Main);
			CombatTarget = nullptr;


			if (Main->CombatTarget == this)
			{
				Main->SetCombatTarget(nullptr);
				Main->bHasCombatTarget = false;
				// search for other combat targets
				Main->UpdateCombatTarget();
			}
	
			if (Main->MainPlayerController)
			{
				USkeletalMeshComponent* MainMesh = Cast<USkeletalMeshComponent>(OtherComp);
				if (MainMesh) Main->MainPlayerController->RemoveEnemyHealthBar();

			}


			// clear timer that handles enemy attack delay, so the enemy wont attack when player isn't in range
			GetWorldTimerManager().ClearTimer(AttackTimer);
		}
	}

}

// make AI move towards player
void AEnemy::MoveToTarget(AMain* Target)
{
	SetEnemyMovementStatus(EEnemyMovmentStatus::EMS_MoveToTarget);

	if (AIController)
	{
		// set the move request for the ai
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(25.f);

		// NavPath initially is empty but one the function that holds the variable is called it will be populated
		FNavPathSharedPtr NavPath;
		AIController->MoveTo(MoveRequest, &NavPath);


		/*
		// draw point that shows the path the ai uses to get to the player
		auto PathPoints = NavPath->GetPathPoints();

		for (auto Point : PathPoints)
		{
			
			FVector Location = Point.Location;
			UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Red, 10.f, 1.5f);
		}
		*/
	}

}


void AEnemy::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// check if main character is being hit by the enemy
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			// play particle when hitting 
			if (Main->HitParticles)
			{
				// call socket attached to the weapon
				const USkeletalMeshSocket* TipSocket = GetMesh()->GetSocketByName("TipSocket");
				// TODO fix the socket location
				if (TipSocket)
				{
					// spawn the emmiter at the spawn location by getting the location of the socket
					FVector SocketLocation = TipSocket->GetSocketLocation(GetMesh());
					// play particle system
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Main->HitParticles, SocketLocation, FRotator(0.f), false);
				}
			}
			// play sound when hitting
			if (Main->HitSound)
			{
				// play sound when enemy hits player
				UGameplayStatics::PlaySound2D(this, Main->HitSound);
			}
			if (DamageTypeClass)
			{
				// this will call the TakeDamage function in the Main.cpp class
				UGameplayStatics::ApplyDamage(Main, Damage, AIController, this, DamageTypeClass);
			}
		}
	}
}


void AEnemy::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// activate collision for the Combatcollision box
void AEnemy::ActivateCollision()
{
	// when called will set collision to query only without physics simulation
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	if (SwingSound)
	{
		// Play swin sound
		UGameplayStatics::PlaySound2D(this, SwingSound);
	}

}

// deactivate collision for the Combatcollision box
void AEnemy::DeactivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// set bAttacking to false
void AEnemy::Attackend()
{
	bAttacking = false;
	// once attacking is done, if player is still overlapping with the enemy combat sphere then call attack again
	if (bOverlappingCombatSphere)
	{
		// delay enemy attack, 
		float AttackTime = FMath::FRandRange(AttackMinTime, AttackMaxTime);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);
	
	}
}

// handle attack 
void AEnemy::Attack()
{
	// only attack if enemy is alive and has a valid alive main character
	if (Alive() && bHasValidTarget)
	{
		if (AIController)
		{
			// when attacking, stop movement
			AIController->StopMovement();
			SetEnemyMovementStatus(EEnemyMovmentStatus::EMS_Attacking);
		}
		if (!bAttacking) // check enemy isnt already in the attacking state
		{
			bAttacking = true;
			// play attacking montage
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_Play(CombatMontage, 1.35f);
				// choosing the section of the montage to be played
				AnimInstance->Montage_JumpToSection(FName("Attack"), CombatMontage);
			}

		}
	}


}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// if enemy health less than zero 
	// decrement health and call die function
	if (Health - DamageAmount <= 0.f)
	{
		Health -= DamageAmount;
		Die(DamageCauser);
	}
	else {
		// else decerement players health
		Health -= DamageAmount;
	}
	return DamageAmount;
}

// play death animation
void AEnemy::Die(AActor* Causer)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage)
	{
		AnimInstance->Montage_Play(CombatMontage, 1.35f);
		// choosing the section of the montage to be played
		AnimInstance->Montage_JumpToSection(FName("Death"), CombatMontage);
	}

	// set status
	SetEnemyMovementStatus(EEnemyMovmentStatus::EMS_Dead);

	// remove collision
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AgroSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bAttacking = false;


	AMain* Main = Cast<AMain>(Causer);
	if (Main)
	{
		Main->UpdateCombatTarget();
	}



}

// called when death animation ends
// stop animation
void AEnemy::DeathEnd()
{
	// stop animating the enemy
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;

	GetWorldTimerManager().SetTimer(DeathTimer, this, &AEnemy::Disappear, DeathDelay);
}
// check if enemy is alive
bool AEnemy::Alive()
{
	return GetEnemyMovementStatus() != EEnemyMovmentStatus::EMS_Dead;
}

void AEnemy::Disappear()
{
	Destroy();
}


