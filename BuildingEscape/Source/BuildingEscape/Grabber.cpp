// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT  //blank/empty macro to help remind us that out parameters are out parameters

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for Duty!"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...

	/// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( 
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation 
		);

	/*
	UE_LOG(LogTemp, Warning, TEXT("Pos is: %s, and Loc is: %s!"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotation.ToString()
		);
	*/

	///Draw a red line to represent the reach
	FVector LineTraceEnd = PlayerViewPointLocation + ReachLength * PlayerViewPointRotation.Vector();
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor::Red,
		false,
		0.0f,
		0.0f,
		10.0f
		);

	///Setup query parameters
	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	/// Line-trace (a.k.a. Ray-cast) out to some reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	/// Check if we hit anything
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}

}

