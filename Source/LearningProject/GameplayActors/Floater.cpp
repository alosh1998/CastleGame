// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// initialize static mesh
	// CreateDefaultSubobject is a template function, meaning that you can tell it what type of object to create using inside the <> <>
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	InitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f, 0.0f, 0.0f);
	initalForce = FVector(2000000.f, 0.0f, 0.0f);
	initalTorque = FVector(2000000.f, 0.0f, 0.0f);
	InitialDirection = FVector(0.0f, 0.0f, 0.0f);

	bInitializeFloaterLocations = false;
	bShouldFloat = false;
	RunningTime = 0.f;

	Amplitude = 1.f;
	TimeStrech = 1.f;




}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();




	// generate random numbers for initial location
	float initialX = FMath::FRandRange(-500.f,500.f);
	float initialY = FMath::FRandRange(-500.f, 500.f);
	float initialZ = FMath::FRandRange(0.f, 500.f);

	// assigning the random numbers to the xyz locations
	InitialLocation.X = initialX;
	InitialLocation.Y = initialY;
	InitialLocation.Z = initialZ;
	
	

	
	

	// placed location will contain the location of the actor when starting play
	PlacedLocation = GetActorLocation();

	if (bInitializeFloaterLocations) {
		// when the game start the setActorlocation will set the location of the actor to the fvector specified below.
		SetActorLocation(InitialLocation);
	}


	
	// AddForce will add force to the object/static Mesh to move 
	//StaticMesh->AddForce(initalForce);

	// AddTorgue will give the object force to spin
	//StaticMesh->AddTorque(initalTorque);



	// AddActorWorldOffset, moves the object according to the world, while AddActorLocalOffset does according to the local object
	// for example if the object is tiltd and we used AddActorWorldOffset with 200f for the x axis, the object will still move according to the world
	// for the same example if we use AddActorLocalOffset, object will move in 200f in the x axis, but when compared to the world it might be in a diagonal postion depending on the object
	//AddActorWorldOffset(LocalOffset, true, &HitResult);


	/* FRotator is responsible for rotating objects.
	 the same principles of localoffset vs worldoffset applies to FRotator as well.
	 eg:
	 FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	 AddActorLocalRotation(Rotation);*/

	
	
	
}

// Called every frame
// delta time is the amount of time in seconds since the last frames
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if should float is set to true object will start moving in the direction specified by initialDirection
	if (bShouldFloat) 
	{
		
		
		// make a hitresult struct.
		// initial value of HitResult is null.
		// it Indicates if this hit was a result of blocking collision.If false, there was no hit or it was an overlap / touch instead.
		//FHitResult HitResult;

		// second paramater is a bool bSweep, if true this object will check for collision even if the other objects simulate physics isn't on.
		// if false, other objects will pass through this object, unless the other objects already have collision defined and simulate physics is set to true.
		// even when the value is true, if one of the objects colliding with each other is already configured to ignore the other object's type, then it collision will not happen.( this can be done by going to the details of the object and change the collision properties
		// in this function because it is going to be called every tick, once a hit has occured the value of HitResult will be assigned value.
		//AddActorLocalOffset(InitialDirection, true, &HitResult);
		

		// store the location of the hit in the variable below
		//FVector HitLocation = HitResult.Location;

///////////////////////////////////////////////////////////////////////
		//This part will make the mesh go up and down, but after adding the x and y location and set y to cos, it will start to move in circle
		// this vector will set actor location
		// get the current location of the actor
		FVector NewLocation = GetActorLocation();

		// sin() will return value from -1 to +1 
		NewLocation.X = NewLocation.X + Amplitude * FMath::Sin(TimeStrech * RunningTime);
		NewLocation.Y = NewLocation.Y + Amplitude * FMath::Cos(TimeStrech * RunningTime);

		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;

////////////////////////////////////////////////////////////////////////
		


	}

}

