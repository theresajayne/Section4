// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Tank Found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Found: %s"), *(ControlledTank->GetName() ));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerControler beginPlay called"));
}
