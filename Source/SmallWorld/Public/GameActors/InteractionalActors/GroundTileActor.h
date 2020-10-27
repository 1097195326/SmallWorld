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

	enum DirectionEnum
	{
		Direction_Up = 1,
		Direction_Down,
		Direction_Left,
		Direction_Right,
		Direction_Other,
	};

	AGroundTileActor();

	//Begin override AGameActor
	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds) override;
	virtual void On_Delete() override;
	//
	void	SetTileSelected(bool);

	void	SetCloudVisible(bool InVisible);
	void	TrackAround();
	//Before Start Game ,Found Soldier In This Tile
	void	TrackSoldier();
	void	SetSoldier(class ASoldierPawn * InSoldier);
	class	ASoldierPawn * GetSoldier() { return Soldier; }

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * GroundTileComponent ;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CloudTileComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent   * CollisionBoxComponent;

	UPROPERTY(EditAnywhere)
		TileTypeEnum  TileType;

	TMap<DirectionEnum, AGameActor*>  AroundActorMap;


protected:

	class ASoldierPawn * Soldier;

};
