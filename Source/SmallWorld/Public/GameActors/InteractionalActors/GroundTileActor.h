#pragma once

#include "GameActor.h"
#include "GameConfig.h"

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

	void SetBusy(bool InBusy) { bIsBusy = InBusy; }
	bool IsBusy() { return bIsBusy; }
	//
	void ShowFlags(bool InMoveFlag,bool InTargetFlag);

	void SetCloudVisible(bool InVisible);
	void TrackAround();
	//Before Start Game ,Found Soldier In This Tile
	void TrackSoldier();
	bool IsHaveSoldier() { return Soldiers.Num() > 0; }
	bool IsHaveFlySoldier();
	void AddSoldier(ASoldierPawn * InSoldier);
	void RemoveSoldier(ASoldierPawn * InSoldier);
	bool IsContain(ASoldierPawn * InSoldier);
	TArray<ASoldierPawn *> GetSoldiers() { return Soldiers; }

	AGroundTileActor* GetAroundTileActorByDistance(int32 InDistance, DirectionEnum InDir, bool InContainSoldier);
	AGroundTileActor* GetHaveSoldierAroundTileActorByDistance(int32 InDistance, DirectionEnum InDir, bool InContainSoldier);
	class ACastleTileActor * GetCastleTileActorByDistance(int32 InDistance, DirectionEnum InDir, bool InContainSoldier);

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * GroundTileComponent ;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CloudTileComponent;
	
	UPROPERTY(EditAnywhere)
		TileTypeEnum  TileType;

	TMap<DirectionEnum, AGameActor*>  AroundActorMap;

	void IncreaseVisibilityCounter() { VisibilityCounter += 1; }
	void DecreaseVisibilityCounter() { VisibilityCounter -= 1; VisibilityCounter < 0 ? VisibilityCounter = 0 : NULL; }
protected:
	bool bIsBusy;
	float FlagTimer;
	AActor * FlagActor;
	TArray<ASoldierPawn*> Soldiers;
	int32 VisibilityCounter;
};
