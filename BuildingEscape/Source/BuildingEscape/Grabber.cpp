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
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Input Component !"), *GetOwner()->GetName());
	}
}

/// find the physics handle
void UGrabber::SetupPhysicsHandleComponent()
{

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// TODO
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physicshandle component !"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab activated !"));

	//LINE TRACE and see if we hit a physics object
	GetFirstPhysicsBodyInReach();
	// attach physics handle if we get a hit
	//TODO: attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released !"));
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	
	/// get player view point 
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation);
	//shal relation
	FVector PlayerViewpointEnd = PlayerViewpointLocation + (Reach * PlayerViewpointRotation.Vector());
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

	return Hit;
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	
	
}



