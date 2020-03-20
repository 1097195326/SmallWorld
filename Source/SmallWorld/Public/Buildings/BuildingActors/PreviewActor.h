#pragma once

#include "CoreMinimal.h"
#include "GameActor.h"
#include "ConstructorHelpers.h"
#include "Components/MeshComponent.h"
#include "BaseBuildingData.h"
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
