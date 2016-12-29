// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber repoting for duty !!"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// get player view point 
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation);
	// logging the coordinates of *location and *rotation
	UE_LOG(LogTemp, Warning, TEXT("location is :%s , roation : %s"),
		*PlayerViewpointLocation.ToString(),
		*PlayerViewpointRotation.ToString());

	// draw a debug line trace 
	FVector PlayerViewpointEnd = PlayerViewpointLocation + ( 100 * PlayerViewpointRotation.Vector());

	DrawDebugLine(
		GetWorld(),
		PlayerViewpointLocation,
		PlayerViewpointEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	// ray-cast to reach certain distance

	// see what we hit 
}

