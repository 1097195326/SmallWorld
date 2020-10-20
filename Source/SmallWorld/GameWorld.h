#pragma once

#include "SmallWorldInstance.h"
#include "GameWorldActor.h"

class ASoldierPawn;
class ABaseBuildingActor;


class GameWorld : public SingleTemplateClass<GameWorld>
{
public:
	GameWorld();
	~GameWorld();

	void ScanWorldMap();
	void BuildGameWorld();
	void RefreshCloudVisible();
	void Update();


private:
	TArray<class AGroundTileActor*> CurrentVisibleGroundArray;
	TArray<class AGroundTileActor*>	GroundActorArray;
	TArray<class ACastleTileActor*>	CastleActorArray;

	AGameWorldActor * GameWorldActor;

	bool IsInitialized;
	bool IsPaused;


};