// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ColliderMovementComponent.h"

// Sets default values
ACollider::ACollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// construct and initilize the root component, every pawn has a root component by default
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// init sphere component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	// attach  component to the root component 
	SphereComponent->SetupAttachment(GetRootComponent());

	// set radius
	SphereComponent->InitSphereRadius(40.f);

	// This is similar to collision presets
	// define what category of collision this object will belong to and therefore we can choose other objects it can collide with
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	//init component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// attach  component to the root component 
	MeshComponent->SetupAttachment(GetRootComponent());


/////////////////////////// Construct and create a visible mesh from c++ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	// this is similar to going to blueprint editor and choosing mesh from the dropdown menu
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	// check to see if the FObjectFinder found the object at the specified location

	if (MeshComponentAsset.Succeeded()) 
	{
		// if yes set the found object to MeshComponent
		//MeshComponentAsset contains a variable named object which stores the actual static mesh
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);

		// set the location of the mesh so that it fits well
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));

		// scale the mesh to fit
		MeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	}
//////////////////////////////////////////////////// End \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	// init component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	// attach  component to the root component 
	SpringArm->SetupAttachment(GetRootComponent());

	// set rotation to look down at the pawn
	//SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);

	// set how far the camera should be away
	SpringArm->TargetArmLength = 400.f;

	// If true, camera lags behind target position to smooth its movement
	SpringArm->bEnableCameraLag = true;

	//If bEnableCameraLag is true, controls how quickly camera reaches target position.
	SpringArm->CameraLagSpeed = 3.0f;






	// construct the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// attach  component to the Spring Arm component, so that the camera location will be according to the spring arm 
	// * by attaching the camera to the spring arm, we can adjust how far the camera is from the player dynamically
	// to use the functions of Camera ,include "Camera/CameraComponent.h"
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

////////////////////////////////////////// Setting movement component//////////////////////////////

	// init 
	OurMovementComponent = CreateDefaultSubobject<UColliderMovementComponent>(TEXT("MovementComponent"));

	// update because we want to move root component when we add movement input to the OurMovementComponent
	OurMovementComponent->UpdatedComponent = RootComponent;


///////////////////////////////////////////////////////////////////////////////////////////////////


	CameraInput = FVector2D(0.f, 0.f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}


// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//////////////////////////////////////// changing the yaw
	// get the rotation of the actor
	// we use the actor rotation status to move yaw
	FRotator NewRotation = GetActorRotation();

	// add the mouse rotation to the yaw value
	NewRotation.Yaw += CameraInput.X ;
	// change the actors rotation according to user input
	SetActorRotation(NewRotation);
////////////////////////////////////////////////////////////

///////////////////////////////////////// changing the pitch
	// to change the pitch we can't use actors location but rather spring arm rotation
	// store springarms current rotation
	FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	// change the pitch according to the user's input
	// using the clamp we will restrict how far the camera can go up and down along the y axis, this will prevent the camera from getting under the player while playing
	// the camera will not go below -80 nor above -15
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, -80.f, -15.f);
	//change the springarms rotation accordingly.
	SpringArm->SetWorldRotation(NewSpringArmRotation);

//////////////////////////////////////////////////////////


}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::YawCamera);

}

void ACollider::MoveForward(float input) 
{
	FVector Forward = GetActorForwardVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(input * Forward);
	}
}
void ACollider::MoveRight(float input) 
{
	FVector Right = GetActorRightVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(input * Right);
	}
}

void ACollider::YawCamera(float AxisValue) 
{
	CameraInput.X = AxisValue;
}

void ACollider::PitchCamera(float AxisValue) 
{
	CameraInput.Y = AxisValue;
}




UPawnMovementComponent* ACollider::GetMovementComponent() const
{
	// return movement component
	// just like getter
	return OurMovementComponent;
}

