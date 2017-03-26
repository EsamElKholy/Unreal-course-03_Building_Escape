// Fill out your copyright notice in the Description page of Project Settings.

#include "Kai_Project.h"
#include "Grabber.h"


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

	// ...
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...	
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetTracedLine().End);
	}

}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s can't find a physics handle component"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabObject);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s can't find an input component"), *GetOwner()->GetName())
	}
}

void UGrabber::GrabObject()
{
	auto hitRes = GetFirstPhysicsBodyInReach();
	auto actor = hitRes.GetActor();

	if (actor)
	{
		if (PhysicsHandle == nullptr)
		{
			return;
		}

		PhysicsHandle->GrabComponent
		(
			hitRes.GetComponent(),
			NAME_None,
			hitRes.GetActor()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::ReleaseObject()
{
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///
	Line tracedLine = GetTracedLine();

	///
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, tracedLine.Start, tracedLine.End, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParams);
		
	return hit;
}

UGrabber::Line UGrabber::GetTracedLine()
{
	FVector playerPos;
	FRotator playerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerPos, playerRotator);
	FVector end = playerPos + playerRotator.Vector() * Reach;

	return Line(playerPos, end);
}