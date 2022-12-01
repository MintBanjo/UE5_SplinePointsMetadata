// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <SplineMetadataDetailsFactory.h>

#include "MySplineMetadataDetails.generated.h"

class FMySplineMetadataDetails;
class UMySplineMetadata;

UCLASS()
class SPMEDITOR_API UMySplineMetadataDetailsFactory : public USplineMetadataDetailsFactoryBase
{
	GENERATED_BODY()

	virtual ~UMySplineMetadataDetailsFactory() {}
	virtual TSharedPtr<ISplineMetadataDetails> Create() override;
	virtual UClass* GetMetadataClass() const override;
};

class SPMEDITOR_API FMySplineMetadataDetails : public ISplineMetadataDetails, public TSharedFromThis<FMySplineMetadataDetails>
{
public:

	virtual ~FMySplineMetadataDetails() {}
	virtual FName GetName() const override;
	virtual FText GetDisplayName() const override;
	virtual void Update(USplineComponent* InSplineComponent, const TSet<int32>& InSelectedKeys) override;
	virtual void GenerateChildContent(IDetailGroup& DetailGroup) override;

private:
	UMySplineMetadata* GetMetadata() const;
	TOptional<float> GetTestFloat() const;
	void OnSetTestFloat(float NewValue, ETextCommit::Type CommitInfo);
	void OnSetValues(FMySplineMetadataDetails& Details);

	TOptional<float> TestFloatValue;
	USplineComponent* SplineComp = nullptr;
	TSet<int32> SelectedKeys;
};
