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
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	///
	FVector playerPos;
	FRotator playerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerPos, playerRotator);

	///
	FVector end = playerPos + playerRotator.Vector() * 100.0f;
	DrawDebugLine(GetWorld(), playerPos, end, FColor(255, 0, 0), false, 0, 0, 10);

	///
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, playerPos, end, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParams);

	///
	AActor *actor = hit.GetActor();
	if (actor)
	{
		// Do Something
		UE_LOG(LogTemp, Warning, TEXT("We hit: %s"), *actor->GetName())
	}
}

