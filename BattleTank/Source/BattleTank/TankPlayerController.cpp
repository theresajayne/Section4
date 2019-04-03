// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


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

void ATankPlayerController::Tick(float DeltaSeconds)
{	
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
	UE_LOG(LogTemp, Warning, TEXT("Ticking"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if(!GetControlledTank())
	{
		return;
	}
	FVector HitLocation; //Out Parameter
	///If it hits the landscape
	if(GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());

		//TODO Tell controlled tank to aim at this point
	}

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	//de-project screen position of the crosshair to a world direction
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
	return true;
	
}

///Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewpoerSizeY;
	GetViewportSize(ViewportSizeX, ViewpoerSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewpoerSizeY*CrossHairYLocation);
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation,LookDirection))
	{
		//Linetrace along that and see what we hit (up to max range)
		if(GetLookVectorHitLocation(LookDirection,HitLocation))
		{
			return true;
		}
		return false;
		
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}


