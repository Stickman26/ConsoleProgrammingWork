// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCube.h"

void AFPSCube::Explode() 
{
	if (!canExplode) 
	{
		FVector Scale = this->GetActorScale();
		Scale *= 0.25f;
		//AFPSCube::StaticClass(), OtherComp->GetComponentLocation(), OtherComp->GetComponentRotation()
		AFPSCube* smallCube = GetWorld()->SpawnActor<AFPSCube>(BlueprintCube, GetActorLocation(), GetActorRotation());
		smallCube->GetRootComponent()->SetWorldScale3D(Scale);
		smallCube->canExplode = true;
	}
	else 
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionTemplate, GetActorLocation());
	}
	
}