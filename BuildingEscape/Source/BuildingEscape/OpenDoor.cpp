// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// Get the owning actor
	AActor* Owner = GetOwner();

	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, 40.0f, 0.0f);

	// Set the door rotation
	Owner->SetActorRelativeRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	//Poll the trigger Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		//If the ActorThatOpens is in the volume
		OpenDoor();
	}
}
