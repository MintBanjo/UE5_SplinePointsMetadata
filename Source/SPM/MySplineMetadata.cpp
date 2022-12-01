// Fill out your copyright notice in the Description page of Project Settings.


#include "MySplineMetadata.h"

void UMySplineMetadata::InsertPoint(int32 Index, float t, bool bClosedLoop)
{
	if (Index >= PointParams.Num())
	{
		AddPoint(static_cast<float>(Index));
	}
	else
	{
		PointParams.Insert(FMySplinePointParams{}, Index);
	}

	Modify();
}

void UMySplineMetadata::UpdatePoint(int32 Index, float t, bool bClosedLoop)
{
	Modify();
}

void UMySplineMetadata::AddPoint(float InputKey)
{
	PointParams.Add(FMySplinePointParams{});
	Modify();
}

void UMySplineMetadata::RemovePoint(int32 Index)
{
	PointParams.RemoveAt(Index);
	Modify();
}

void UMySplineMetadata::DuplicatePoint(int32 Index)
{
	FMySplinePointParams NewVal = PointParams[Index];
	PointParams.Insert(NewVal, Index);
	Modify();
}

void UMySplineMetadata::CopyPoint(const USplineMetadata* FromSplineMetadata, int32 FromIndex, int32 ToIndex)
{
	if (const UMySplineMetadata* FromMetadata = Cast<UMySplineMetadata>(FromSplineMetadata))
	{
		PointParams[ToIndex] = PointParams[FromIndex];
		Modify();
	}
}

void UMySplineMetadata::Reset(int32 NumPoints)
{
	PointParams.Reset(NumPoints);
	Modify();
}

void UMySplineMetadata::Fixup(int32 NumPoints, USplineComponent* SplineComp)
{
	if (PointParams.Num() > NumPoints)
	{
		PointParams.RemoveAt(NumPoints, PointParams.Num() - NumPoints);
		Modify();
	}

	while (PointParams.Num() < NumPoints)
	{
		PointParams.Add(FMySplinePointParams{});
		Modify();
	}
}
