// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();	
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller No Player Tank Found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Found: %s"), *(PlayerTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AI Controller beginPlay called"));
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn =  GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!PlayerPawn)
	{
		return nullptr;
	}	
	return Cast<ATank>(PlayerPawn);
}
