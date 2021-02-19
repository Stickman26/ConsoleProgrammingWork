// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCube.h"

// Sets default values
AFPSCube::AFPSCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

