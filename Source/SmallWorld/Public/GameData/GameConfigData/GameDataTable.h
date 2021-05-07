#pragma once
#include "CoreMinimal.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "GameDataTable.generated.h"



USTRUCT()
struct FResourceTableRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		FString  ResourceName;
	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UObject> ResourcePath;
	UPROPERTY(EditAnywhere)
		FRotator RelativeRotation;
	UPROPERTY(EditAnywhere)
		FVector RelativeScale;

	FResourceTableRow():
		RelativeScale(FVector::OneVector)
	{}

};




