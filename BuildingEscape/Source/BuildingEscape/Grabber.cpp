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

	SetupInputComponent();
	SetupPhysicsHandleComponent();
}

/// find the input component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		// bind key with events
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an Input Component !"), *GetOwner()->GetName());
	}
}

/// find the physics handle
void UGrabber::SetupPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physicshandle component !"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	if (PhysicsHandle == nullptr) { return; }
	//LINE TRACE and see if we hit a physics object
	FHitResult hit = GetFirstPhysicsBodyInReach();
	// attach physics handle if we get a hit
	auto ActorHit = hit.GetActor();
	auto ComponentToGrab = hit.GetComponent();
	if (ActorHit)
	{
		// attach physics handle
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ActorHit->GetActorLocation(),
			ActorHit->GetActorRotation()
		);
	}
}
/// release the grabbed physics object
void UGrabber::Release()
{
	if (PhysicsHandle == nullptr) { return; }
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// get player view point 
	GetFirstPlayerViewPoint();
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
	return Hit;
}

void UGrabber::GetFirstPlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation);
	PlayerViewpointEnd = PlayerViewpointLocation + (Reach * PlayerViewpointRotation.Vector());
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (PhysicsHandle == nullptr) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		GetFirstPlayerViewPoint();
		PhysicsHandle->SetTargetLocation(PlayerViewpointEnd);
	}
}