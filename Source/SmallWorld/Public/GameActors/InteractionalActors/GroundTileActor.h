#pragma once

#include "GameActor.h"

#include "GroundTileActor.generated.h"

UENUM()
enum class TileTypeEnum : uint8
{
	E_None,
	E_Used,
	E_CanNotUse,
	E_Num
};

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

	void	TrackAround();

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * GroundTileComponent ;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CloudTileComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent   * CollisionBoxComponent;

	UPROPERTY(EditAnywhere)
		TileTypeEnum  TileType;

};
