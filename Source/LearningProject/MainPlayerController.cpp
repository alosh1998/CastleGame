// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay() 
{

	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		// set the actuall hud overlay
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	// add it to the viewport
	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	if (WEnemyHealthBar)
	{
		// create the widget
		EnemyHealthBar = CreateWidget<UUserWidget>(this, WEnemyHealthBar);

		if (EnemyHealthBar)
		{
			EnemyHealthBar->AddToViewport();
			EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden); 
		}
		FVector2D Alignment(0.f, 0.f);
		EnemyHealthBar->SetAlignmentInViewport(Alignment);
	}
}

// show enemy health bar
void AMainPlayerController::DisplayEnemyHealthBar()
{
	if (EnemyHealthBar)
	{
		bEnemyHealthBarVisible = true;
		EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);

	}
}
void AMainPlayerController::RemoveEnemyHealthBar()
{
	if (EnemyHealthBar)
	{
		bEnemyHealthBarVisible = false;
		EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);

	}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyHealthBar)
	{
		FVector2D PositionOnViewPort;
		// this function will project given 2D vector into the world
		ProjectWorldLocationToScreen(EnemyLocation,PositionOnViewPort);
		PositionOnViewPort.Y -= 85.f;
		// size of the health bar in screen
		FVector2D SizeInViewPort(300.f, 25.f);

		// set the position of the healthbar
		EnemyHealthBar->SetPositionInViewport(PositionOnViewPort);

		// set the size of the health bar
		EnemyHealthBar->SetDesiredSizeInViewport(SizeInViewPort);
	}
}
