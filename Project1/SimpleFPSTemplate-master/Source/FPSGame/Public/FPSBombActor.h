// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "FPSBombActor.generated.h"

UCLASS()
class FPSGAME_API AFPSBombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBombActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UParticleSystem* ExplosionTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	float ExplodeDelay;

	UFUNCTION()
	void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
