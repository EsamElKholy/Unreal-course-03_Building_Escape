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
	OriginalRotation = GetOwner()->GetTransform().GetRotation();
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

			DoorLastCloseCheck = GetWorld()->GetTimeSeconds();
			DoorIsClosed = false;
		}

		if (!DoorIsClosed)
		{
			if (GetWorld()->GetTimeSeconds() - DoorLastCloseCheck > DoorCloseDelay)
			{
				CloseTheDoor();
				DoorIsClosed = true;
			}
		}
	}	
}

void UOpenDoor::OpenTheDoor()
{
	GetOwner()->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UOpenDoor::CloseTheDoor()
{
	GetOwner()->SetActorRotation(OriginalRotation);
}

AActor* UOpenDoor::GetPlayerPawn() 
{
	AActor *pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	return pawn;
}

