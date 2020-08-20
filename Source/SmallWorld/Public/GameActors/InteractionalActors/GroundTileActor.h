#pragma once

#include "GameActor.h"

#include "GroundTileActor.generated.h"


UCLASS()
class AGroundTileActor : public AGameActor
{
public:
	GENERATED_BODY()

	AGroundTileActor();

	//Begin override AGameActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;

	

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * GroundTileComponent ;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CloudTileComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent   * CollisionBoxComponent;



};
