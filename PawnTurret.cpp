// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
	
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
    
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > MaxRange) 
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
    //call base pawn class to handle special effects, etc.
    Super::HandleDestruction();
    Destroy();
}

void APawnTurret::CheckFireCondition()
{
    //If dead, stop shooting :/ - GetPlayer Pawn needs a reference object from the world and
    //a reference to which pawn we are looking for. In this case we only have one player, so 
    //the player number would be 0.
    if(!PlayerPawn) // Crash Protection
    {
        return;
    }

    //if the player is in range, then shoot
    if(ReturnDistanceToPlayer() <= MaxRange)
    {
        //Fire
        Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }
    
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
