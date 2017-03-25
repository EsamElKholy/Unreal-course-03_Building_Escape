// Fill out your copyright notice in the Description page of Project Settings.

#include "Kai_Project.h"
#include "OpenDoor.h"


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

	// ...
	ActorThatOpensDoor = GetPlayerPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (ActorThatOpensDoor)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
		{
			OpenTheDoor();
		}
	}	
}

void UOpenDoor::OpenTheDoor()
{
	FRotator rotator = FRotator(0, 90.0f, 0);

	GetOwner()->SetActorRotation(rotator);
}

AActor* UOpenDoor::GetPlayerPawn() 
{
	AActor *pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	return pawn;
}

