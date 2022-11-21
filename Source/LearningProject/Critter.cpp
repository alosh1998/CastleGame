// Fill out your copyright notice in the Description page of Project Settings.


#include "Critter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ACritter::ACritter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// construct and initilize the root component, every pawn has a root component by default
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// construct the mesh
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));

	// attach mesh component to the root component 
	// to use the functions of StaticMesh ,include "Components/StaticMeshComponent.h"
	MeshComponent->SetupAttachment(GetRootComponent());


	// construct the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	// attach  component to the root component 
	// to use the functions of Camera ,include "Camera/CameraComponent.h"
	Camera->SetupAttachment(GetRootComponent());

	// to set the location of the camera
	Camera->SetRelativeLocation(FVector(-300.f,0.f,300.f));

	// set rotation
	Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	// to set the Camera defined earlier as the main earlier we have to do the following
	// Player0 is the main player in singleplayer game, and the first player in multiplayer games.
	// this part allows us to possess the default pawn
	// AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurrentVelocity = FVector(0.f);

	MaxSpeed = 100.f;

}

// Called when the game starts or when spawned
void ACritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// new location will update the value of new location based on the currentVelocity which is updated according to the user input
	FVector NewLcoation = GetActorLocation() + (CurrentVelocity * DeltaTime);

	// set the location of the actor to the new location
	SetActorLocation(NewLcoation);

}

// Called to bind functionality to input
void ACritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// after defining the input details in the project settings\Input\Axis Mapping,
	// here we will bind the settings to functions, using BinAxis
	// in the example below, 
	// first paramater is the name used in the Axis mapping settings, then the current object, then the address of the function we want to map with the input
	// in this part, when up key, w, S or down key is pressed the MoveForward() will be called and the value of the axis will be the paramerter 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACritter::MoveForward);


	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACritter::MoveRight);

}
// handles the mechanics of making the pawn move forward and backward
void ACritter::MoveForward(float Value) {

	// clamp function will make sure the value passed is between the max and min values, eg if value is 10 clamp will make it 1
	// the value of CurrentVelocity.Y will be changed according to the user input
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f)*MaxSpeed;

}
// handles the mechanics of making the pawn move right and left
void ACritter::MoveRight(float Value) {
	
	// clamp function will make sure the value passed is between the max and min values, eg if value is 10 clamp will make it 1
	// the value of CurrentVelocity.X will be changed according to the user input
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;

}

