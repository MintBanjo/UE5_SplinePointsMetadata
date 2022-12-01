// Fill out your copyright notice in the Description page of Project Settings.

#include "MySplineComponent.h"

#include "MySplineActor.h"
#include "MySplineMetadata.h"

USplineMetadata* UMySplineComponent::GetSplinePointsMetadata()
{
	if (AMySplineActor* Actor = Cast<AMySplineActor>(GetOwner()))
	{
		return Actor->GetSplineMetadata();
	}

	return nullptr;
}

const USplineMetadata* UMySplineComponent::GetSplinePointsMetadata() const
{
	return GetSplinePointsMetadata();
}

void UMySplineComponent::FixupPoints()
{
#if WITH_EDITORONLY_DATA
	// Keep metadata in sync
	if (GetSplinePointsMetadata())
	{
		const int32 NumPoints = GetNumberOfSplinePoints();
		GetSplinePointsMetadata()->Fixup(NumPoints, this);
	}
#endif
}

void UMySplineComponent::PostLoad()
{
	Super::PostLoad();

	FixupPoints();
}

void UMySplineComponent::PostDuplicate(bool bDuplicateForPie)
{
	Super::PostDuplicate(bDuplicateForPie);

	FixupPoints();
}

#if WITH_EDITOR
void UMySplineComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FixupPoints();
}

void UMySplineComponent::PostEditImport()
{
	Super::PostEditImport();

	FixupPoints();
}
#endif
