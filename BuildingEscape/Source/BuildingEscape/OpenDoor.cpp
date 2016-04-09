// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT  //blank/empty macro to help remind us that out parameters are out parameters

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();

	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a pressure plate (trigger vol.)"), *(GetOwner()->GetName()));
	}
}



// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll the trigger Volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) 
	{
		//If the ActorThatOpens is in the volume
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check  if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) 
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{

	Owner->SetActorRelativeRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor() 
{
	Owner->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
	float TotalMass = 0.0f;
	// Find all overlapping actors
	TArray<AActor*> ActorsOnPlate; 
	if (!PressurePlate) { return -1.0f; }
	PressurePlate->GetOverlappingActors(OUT ActorsOnPlate);

	// Iterate through them adding their masses
	for (auto& Actor : ActorsOnPlate)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate."), *(Actor->GetName()));
	}
	return TotalMass;
}