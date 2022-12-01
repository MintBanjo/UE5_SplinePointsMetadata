// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "MySplineActor.generated.h"

class UMySplineMetadata;
class UMySplineComponent;

UCLASS()
class SPM_API AMySplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMySplineActor();
	UMySplineMetadata* GetSplineMetadata() const;

private:
	UPROPERTY(Instanced, Export)
	UMySplineMetadata* MySplineMetadata = nullptr;

	UPROPERTY(VisibleAnywhere)
	UMySplineComponent* MySplineComponent = nullptr;
};
