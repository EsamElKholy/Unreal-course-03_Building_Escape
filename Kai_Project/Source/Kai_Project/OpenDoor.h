// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KAI_PROJECT_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

private:
	void OpenTheDoor();
	void CloseTheDoor();

	AActor* GetPlayerPawn();

	float GetTotalMassOnPlate();

private:
	FQuat OriginalRotation;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;

	float DoorLastCloseCheck;

	bool DoorIsClosed;
};
