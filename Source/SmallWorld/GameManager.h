#pragma once

#include "GameWorldActor.h"

class ASoldierPawn;
class ABaseBuildingActor;


class GameManager : public SingleTemplateClass<GameManager>
{
public:
	GameManager();
	~GameManager();

	void ScanWorldMap();
	void BuildGameWorld();
	void RefreshCloudVisible();
	void Update(float DeltaTime);


private:
	TArray<class AGroundTileActor*> CurrentVisibleGroundArray;
	TArray<class AGroundTileActor*>	GroundActorArray;
	TArray<class ACastleTileActor*>	CastleActorArray;

	AGameWorldActor * GameWorldActor;

	bool IsInitialized;
	bool IsPaused;


};