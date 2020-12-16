#pragma once

#include "GameActor.h"

#include "CastleTileActor.generated.h"


UCLASS()
class ACastleTileActor : public AGameActor
{
public:
	GENERATED_BODY()

	
	ACastleTileActor();

	//Begin override AGameActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	void TrackAround();
	void SignAround();
	void SetBuildingActor(class ABaseBuildingActor * InActor);
	class ABaseBuildingActor * GetBuildingActor() { return BuildingActor; }
	TArray<class AGroundTileActor*> GetAroundActors() { return AroundActorArray; }

protected:

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CastleTileComponent ;
	UPROPERTY(VisibleDefaultsOnly)
		UInstancedStaticMeshComponent * CloudTileComponent;
	
	TArray<class AGroundTileActor*>  AroundActorArray;
	class ABaseBuildingActor * BuildingActor;
};
