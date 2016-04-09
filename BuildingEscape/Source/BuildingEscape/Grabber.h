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

private:
	
	//How far the player's reach is (in cm) to pick up objects
	UPROPERTY(EditAnywhere)
		float ReachLength = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	// Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	UInputComponent* InputComponent = nullptr;
	// Setup (assumed) attached input component
	void SetupInputComponent();

	//Ray-Cast and grab object in reach
	void Grab();
	//Release any grabbed object
	void Release();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Returns current end of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();
};
