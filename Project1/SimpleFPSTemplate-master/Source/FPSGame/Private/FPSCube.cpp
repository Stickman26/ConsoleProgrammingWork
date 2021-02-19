// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCube.h"

void AFPSCube::Explode() 
{

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionTemplate, GetActorLocation());
}