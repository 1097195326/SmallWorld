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

	void	TrackAround();

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CastleTileComponent ;
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent   * CollisionBoxComponent;


	TArray<class AGroundTileActor*>  AroundActorArray;

};
