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
	
	UE_LOG(LogTemp, Warning, TEXT("Grabber repoting for duty !!"))
	
	// find the physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//check if the physics handle were found
	if (PhysicsHandle)
	{
		// TODO
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physicshandle component !"),*GetOwner()->GetName());
	}

	// find the input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	//check if the input component were found
	if (InputComponent)
	{
		// bind key with events
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Input Component !"), *GetOwner()->GetName());
	}


}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab activated !"));
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// get player view point 
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation);

	/// draw a debug line trace 
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

	/// ray-cast to reach certain distance
	FHitResult Hit;
	FCollisionQueryParams Params(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		PlayerViewpointEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		Params
	);
	/// see what we hit 
	AActor* HitObject = Hit.GetActor();
	if (HitObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("you did hit : %s"), *HitObject->GetName())
	}
	
}



