// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
/************************************************************************************************************/
	// setting collision for the trigger box

	/** QueryOnly: Only used for spatial queries (raycasts, sweeps, and overlaps). 
	Cannot be used for simulation (rigid body, constraints).
	Useful for character movement and things that do not need physical simulation. 
	Performance gains by keeping data out of simulation tree. */
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);// ignore all other objects
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);// overlap with only Pawn




/************************************************************************************************************/
	// set the extents for the box
	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));



	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	SwitchTime = 2.f;
	bCharacterOnSwitch = false;
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	 
	//OnComponentBeginOverlap is similar to OnClickListener in java, it triggers function if overlap happens

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin);

	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd);

	// get init location for the door
	InitialDoorLocation = Door->GetComponentLocation();
	// get init location for the switch
	InitialSwitchLocation = FloorSwitch->GetComponentLocation();
	
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// the param are brought from PrimitiveComponent.h
void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap begin."));
	if (!bCharacterOnSwitch) bCharacterOnSwitch = true;
	RaiseDoor();
	LowerFloorSwitch();

}
// the param are brought from PrimitiveComponent.h
void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End."));
	if (bCharacterOnSwitch) bCharacterOnSwitch = false;
	// use timer to delay closing door
	GetWorldTimerManager().SetTimer(SwitchHandle, this, &AFloorSwitch::CloseDoor, SwitchTime);

}

// update the location of the door according
void AFloorSwitch::UpdateDoorLocation(float Z)
{

	FVector NewLcoation = InitialDoorLocation;
	NewLcoation.Z += Z;
	Door->SetWorldLocation(NewLcoation);

}
void AFloorSwitch::UpdateFloorSwitchLocation(float Z) {
	FVector NewLcoation = InitialSwitchLocation;
	NewLcoation.Z += Z;
	FloorSwitch->SetWorldLocation(NewLcoation);
}

void AFloorSwitch::CloseDoor() {
	if (!bCharacterOnSwitch) {

		LowerDoor();
		RaiseFloorSwitch();
	}
	
}
