// Fill out your copyright notice in the Description page of Project Settings.

#include "MySplineActor.h"

#include "MySplineMetadata.h"

AMySplineActor::AMySplineActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MySplineMetadata = CreateDefaultSubobject<UMySplineMetadata>(TEXT("MySplineMetadata"));
	MySplineMetadata->Reset(2);
	MySplineMetadata->AddPoint(0.0f);
	MySplineMetadata->AddPoint(1.0f);

	MySplineComponent = CreateDefaultSubobject<UMySplineComponent>(TEXT("MySplineComponent"));
	SetRootComponent(MySplineComponent);
}

UMySplineMetadata* AMySplineActor::GetSplineMetadata() const 
{ 
	return MySplineMetadata; 
}

float AMySplineActor::GetTestFloatAtSplinePoint(int32 PointIndex)
{
	if (ensure(MySplineMetadata))
	{
		if (ensure(MySplineMetadata->PointParams.IsValidIndex(PointIndex)))
		{
			return MySplineMetadata->PointParams[PointIndex].TestFloat;
		}
	}

	return 0.0f;
}

