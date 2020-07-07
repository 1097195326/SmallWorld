#pragma once

#include "GameActor.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "MapActor.generated.h"



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

	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * GroundMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * CloudMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * FenceMeshComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * CityMeshComponent;

};