// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor();
	void CloseDoor();


private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 75.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	//UPROPERTY(EditAnywhere)
	AActor* Owner = nullptr; //the owning door

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.6f;

	float LastDoorOpenTime;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 50.0f;

	//Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
