// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private :

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// grab when pressed 
	void Grab();
	// when release the grab
	void Release();

	///find the physics handle component
	void SetupPhysicsHandleComponent();

	/// find input component and setup keymapping
	void SetupInputComponent();

	/// get the first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
