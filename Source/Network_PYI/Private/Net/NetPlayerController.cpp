// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/NetPlayerController.h"
#include "Net/NetHUDWidget.h"

void ANetPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UNetHUDWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
