#pragma once

#include "GameActor.h"
#include "GameConfig.h"

#include "GroundTileActor.generated.h"

class ASoldierPawn;

UENUM()
enum class TileTypeEnum : uint8
{
	TileType_None,
	TileType_Water,
	TileType_Lava,
	TileType_Land,
	TileType_Num
};
UENUM()
enum class TileSignEnum : uint32
{
	TileSign_None,
	TileSign_Way = 1,
	TileSign_Block = 1 << 1,
	TileSign_Target = 1 << 2,
	TileSign_Castle = 1 << 3,

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
		Direction_Num
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
	bool IsHaveFlySoldier();

	bool IsHaveGameActor() { return GameActors.Num() > 0; }
	void AddGameActor(AActor * InActor);
	void RemoveGameActor(AActor * InActor);
	bool IsContainGameActor(AActor * InActor);
	TArray<AActor *> GetGameActors() { return GameActors; }

	AGroundTileActor* GetAroundTileActorByDistance(int32 InDistance, DirectionEnum InDir, bool InContainSoldier);
	AGroundTileActor* GetHaveSoldierAroundTileActorByDistance(int32 InDistance, DirectionEnum InDir);
	class ACastleTileActor * GetCastleTileActorByDistance(int32 InDistance, DirectionEnum InDir, bool InContainSoldier);

	bool IsVisible() { return VisibilityCounter > 0; }
	void IncreaseVisibilityCounter() { VisibilityCounter += 1; }
	void DecreaseVisibilityCounter() { VisibilityCounter -= 1; VisibilityCounter < 0 ? VisibilityCounter = 0 : NULL; }

	int32 GetSignIndex() { return TileSignIndex; }

	TMap<DirectionEnum, AGameActor*>  AroundActorMap;

protected:
	bool bIsBusy;
	float FlagTimer;
	AActor * FlagActor;
	TArray<AActor*> GameActors;
	int32 VisibilityCounter;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * GroundTileComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent * CloudTileComponent;

	UPROPERTY(EditAnywhere , Category = "Setting")
		TileTypeEnum  TileType;
	UPROPERTY(EditAnywhere, Category = "Setting")
		TileSignEnum  TileSign;
	UPROPERTY(EditAnywhere, Category = "Setting")
		int32 TileSignIndex;
};
