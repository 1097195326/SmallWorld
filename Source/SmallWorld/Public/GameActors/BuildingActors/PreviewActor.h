#pragma once

#include "CoreMinimal.h"
#include "GameActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/MeshComponent.h"
#include "BaseBuildingDataClass.h"
#include "PreviewActor.generated.h"

UCLASS()
class APreviewActor : public AGameActor
{
public:
	GENERATED_BODY()
	APreviewActor();

	bool SetMeshComponent(const FString & InName);

	FString IconName;
private:
	UMeshComponent * MeshComponent;


};
