#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"
#include "GameDataManager.h"
#include "SoldierPawn.h"
#include "BaseBuildingActor.h"


GameWorld::GameWorld()
{
	IsInitialized = false;
	IsPaused = false;

	GameWorldActor = nullptr;
}
GameWorld::~GameWorld()
{
	GameWorldActor = nullptr;
}
void GameWorld::BuildTileWorld()
{
	
	
	IsInitialized = true;
}
void GameWorld::Update()
{

	if (IsInitialized)
	{
		
	}
}