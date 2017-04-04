// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no pressure plate assigned !"), *GetOwner()->GetName());
	}
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 90.f, 0.f));
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// poll triggervolume for actor overlaps 
	if (PressurePlate == nullptr) { return; }
	
	if (GetTotalMassOverlappingActors() > TriggerMass)
	{
		OnOpen.Broadcast();
	}else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOverlappingActors()
{
	float TotalMass = 0.f;
	TArray<AActor *> OverlappingActors;
	//find all overlapping actors 
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// iterate through overlapping actors and sum their masses
	for (auto& Actor : OverlappingActors)
	{
		float ActorMass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += ActorMass;
	}
	return TotalMass;
}
		

