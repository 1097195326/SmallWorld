#pragma once

#include "GameActor.h"

#include "GroundTileActor.generated.h"

class ASoldierPawn;

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
		Direction_Forward = 1,
		Direction_Back,
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
	void	ShowFlags(bool InMoveFlag,bool InTargetFlag);

	void	SetCloudVisible(bool InVisible);
	void	TrackAround();
	//Before Start Game ,Found Soldier In This Tile
	void	TrackSoldier();
	bool	HaveSoldiers() { return Soldiers.Num() > 0; }
	void	AddSoldier(ASoldierPawn * InSoldier);
	void	RemoveSoldier(ASoldierPawn * InSoldier);
	bool	IsContain(ASoldierPawn * InSoldier);
	TArray<ASoldierPawn *> GetSoldiers() { return Soldiers; }

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
	float  FlagTimer;
	AActor* FlagActor;
	TArray<ASoldierPawn*> Soldiers;
	
};
