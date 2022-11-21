// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	/** reference to the UMG asset in the editor */
	// using TSubclassOf: in the blueprint we will have a dropdown menu of classes that are subclasses of <Templat> 
	// this way we can assign a blueprint to a variable in c++ class, by choosing from the dropdown menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	/** variable to hold the widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WEnemyHealthBar;

	/** variable to hold the widget after creating it */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* EnemyHealthBar;

	// enemy health bar

	bool bEnemyHealthBarVisible;

	void DisplayEnemyHealthBar();
	void RemoveEnemyHealthBar();

	FVector EnemyLocation;



protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};
