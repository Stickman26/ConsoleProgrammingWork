// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCube.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSCube : public AStaticMeshActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		TSubclassOf<AFPSCube> BlueprintCube;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		UParticleSystem* ExplosionTemplate;

public:

	UFUNCTION()
		void Explode();

};
