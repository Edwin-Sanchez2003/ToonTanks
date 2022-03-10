// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "AirPlane.h"


// Sets default values
AAirPlane::AAirPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a settable static mesh component
	AirplaneMesh = CreateDefaultSubobject<UStaticMeshComponent>("AirPlaneMesh");
}

// Called when the game starts or when spawned
void AAirPlane::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAirPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AAirPlane::Move() {
	MoveDirection = FVector(0, MoveSpeed * GetWorld()->DeltaTimeSeconds, 0);
	AddActorLocalOffset(MoveDirection, true);
}

void AAirPlane::Rotate() {
	FRotator Rotation = FRotator(0, -90, 0);
	AirplaneMesh->SetRelativeRotation(Rotation);
	/*
	float RotateAmount = RotateSpeed * GetWorld()->DeltaTimeSeconds;
    
    RotationDirection = FQuat(Rotation);
	AddActorLocalRotation(RotationDirection, true);
	*/
}

