// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCube.h"

void AFPSCube::Explode() 
{
	if (!canExplode) 
	{
		FVector Scale = this->GetActorScale();
		Scale *= 0.25f;
		
		float OffScale = 10.0f;

		FVector Offsets[] = {
			FVector(1,1,0),
			FVector(1,-1,0),
			FVector(-1,-1,0),
			FVector(-1,1,0)
		};

		for (int x = 0; x < 4; ++x)
		{
			AFPSCube* smallCube = GetWorld()->SpawnActor<AFPSCube>(BlueprintCube, GetActorLocation() + (Offsets[x] * OffScale * this->GetActorScale().X), GetActorRotation());
			smallCube->GetRootComponent()->SetWorldScale3D(Scale);
			smallCube->canExplode = true;
		}
	}
	else 
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionTemplate, GetActorLocation());
	}
	
}