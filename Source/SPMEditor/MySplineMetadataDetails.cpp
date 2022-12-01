// Fill out your copyright notice in the Description page of Project Settings.


#include "MySplineMetadataDetails.h"

#include <IDetailGroup.h>
#include <DetailLayoutBuilder.h>
#include <DetailWidgetRow.h>
#include <Widgets/Input/SNumericEntryBox.h>
#include <ScopedTransaction.h>
#include <ComponentVisualizer.h>
#include <Editor.h>

#include "SPM/MySplineMetadata.h"

#define LOCTEXT_NAMESPACE "FMySplineMetadataDetails"

TSharedPtr<ISplineMetadataDetails> UMySplineMetadataDetailsFactory::Create()
{
	return MakeShared<FMySplineMetadataDetails>();
}

UClass* UMySplineMetadataDetailsFactory::GetMetadataClass() const
{
	return UMySplineMetadata::StaticClass();
}

FName FMySplineMetadataDetails::GetName() const
{
	return FName(TEXT("MySplineMetadataDetails"));
}

FText FMySplineMetadataDetails::GetDisplayName() const
{
	return LOCTEXT("MySplineMetadataDetails", "SPM");
}

template<class T>
bool UpdateMultipleValue(TOptional<T>& CurrentValue, T InValue)
{
	if (!CurrentValue.IsSet())
	{
		CurrentValue = InValue;
	}
	else if (CurrentValue.IsSet() && CurrentValue.GetValue() != InValue)
	{
		CurrentValue.Reset();
		return false;
	}

	return true;
}

void FMySplineMetadataDetails::Update(USplineComponent* InSplineComponent, const TSet<int32>& InSelectedKeys)
{
	SplineComp = InSplineComponent;
	SelectedKeys = InSelectedKeys;
	TestFloatValue.Reset();

	if (InSplineComponent)
	{
		bool bUpdateTestFloat = true;

		UMySplineMetadata* Metadata = Cast<UMySplineMetadata>(InSplineComponent->GetSplinePointsMetadata());
		if (Metadata)
		{
			for (int32 Index : InSelectedKeys)
			{
				if (Metadata->PointParams.IsValidIndex(Index))
				{
					if (bUpdateTestFloat)
					{
						bUpdateTestFloat = UpdateMultipleValue(TestFloatValue, Metadata->PointParams[Index].TestFloat);
					}
				}
			}
		}
	}
}

void FMySplineMetadataDetails::GenerateChildContent(IDetailGroup& DetailGroup)
{
	DetailGroup.AddWidgetRow()
		.Visibility(EVisibility::Visible)
		.NameContent()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TestFloat", "TestFloat"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	.ValueContent()
		.MinDesiredWidth(125.0f)
		.MaxDesiredWidth(125.0f)
		[
			SNew(SNumericEntryBox<float>)
			.Value(this, &FMySplineMetadataDetails::GetTestFloat)
		.AllowSpin(false)
		.MinValue(0.0f)
		.MaxValue(TOptional<float>())
		.MinSliderValue(0.0f)
		.MaxSliderValue(TOptional<float>()) // No upper limit
		.UndeterminedString(LOCTEXT("Multiple", "Multiple"))
		.OnValueCommitted(this, &FMySplineMetadataDetails::OnSetTestFloat)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		];
}

void FMySplineMetadataDetails::OnSetValues(FMySplineMetadataDetails& Details)
{
	Details.SplineComp->GetSplinePointsMetadata()->Modify();
	Details.SplineComp->UpdateSpline();
	Details.SplineComp->bSplineHasBeenEdited = true;
	static FProperty* SplineCurvesProperty = FindFProperty<FProperty>(USplineComponent::StaticClass(), GET_MEMBER_NAME_CHECKED(USplineComponent, SplineCurves));
	FComponentVisualizer::NotifyPropertyModified(Details.SplineComp, SplineCurvesProperty);
	Details.Update(Details.SplineComp, Details.SelectedKeys);

	GEditor->RedrawLevelEditingViewports(true);
}

void FMySplineMetadataDetails::OnSetTestFloat(float NewValue, ETextCommit::Type CommitInfo)
{
	if (UMySplineMetadata* Metadata = GetMetadata())
	{
		const FScopedTransaction Transaction(LOCTEXT("SetTestFloat", "Set spline point test float"));

		for (int32 Index : SelectedKeys)
		{
			Metadata->PointParams[Index].TestFloat = NewValue;
		}

		OnSetValues(*this);
	}
}

UMySplineMetadata* FMySplineMetadataDetails::GetMetadata() const
{
	UMySplineMetadata* Metadata = SplineComp ? Cast<UMySplineMetadata>(SplineComp->GetSplinePointsMetadata()) : nullptr;
	return Metadata;
}

TOptional<float> FMySplineMetadataDetails::GetTestFloat() const 
{ 
	return TestFloatValue; 
}

#undef LOCTEXT_NAMESPACE