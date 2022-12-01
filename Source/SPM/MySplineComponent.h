// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Components/SplineComponent.h>

#include "MySplineComponent.generated.h"

USTRUCT()
struct FMySplinePointParams
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TestFloat = 1.0f;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class SPM_API UMySplineComponent : public USplineComponent
{
	GENERATED_BODY()

public:
	virtual USplineMetadata* GetSplinePointsMetadata();
	virtual const USplineMetadata* GetSplinePointsMetadata() const;
	virtual void PostLoad() override;
	virtual void PostDuplicate(bool bDuplicateForPie) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditImport() override;
#endif
	void FixupPoints();
};
