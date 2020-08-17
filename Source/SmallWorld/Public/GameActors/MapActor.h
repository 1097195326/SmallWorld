#pragma once

#include "GameConfig.h"

#include "GameActor.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "MapActor.generated.h"

using namespace TileGameConfig;

UCLASS()
class AMapActor : public AGameActor
{
	GENERATED_BODY()
public:
	AMapActor();

	//Begin override AGameActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;
	//End AGameActor
	int32	AddGroupInstance(const FVector& InLocation);
	int32	AddCloudInstance(const FVector& InLocation);

	FVector GetGroupInstanceLocation(const int32 & inIndex);
	void	SetCloudInstanceVisible(const int32 & InIndex, const bool & InIsVisible);


	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * GroundMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * CloudMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * FenceMeshComponent;

};