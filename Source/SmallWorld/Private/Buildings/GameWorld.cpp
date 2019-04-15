#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"

GameWorld::GameWorld()
{
	CitySize = 2;
}
GameWorld::~GameWorld()
{

}
GameWorld::GameWorld(const GameWorld & _world)
{
	
}
GameWorld & GameWorld::operator = (const GameWorld & _world)
{
	return *this;
}
GameWorld * GameWorld::GetInstance()
{
	static GameWorld world;
	return &world;
}
void GameWorld::InitWithGameInstance(USmallWorldInstance * _GameInstance)
{
	mGameInstance = _GameInstance;
}
void GameWorld::BuildWorld()
{

	for (int x = 0; x < WorldSize; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			FTransform trans;
			ACityActor * CityActor = Cast<ACityActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(mGameInstance, ACityActor::StaticClass(), trans));
			if (CityActor)
			{
				CityActor->SetIndex(FBuildingIndex(x, y));
				UGameplayStatics::FinishSpawningActor(CityActor, trans);

				CityMap[x][y] = CityActor;
			}
		}
	}
	/*FTransform trans;
	ABlockActor * BlockActor = Cast<ABlockActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(mGameInstance, ABlockActor::StaticClass(), trans));
	if (BlockActor)
	{

		UGameplayStatics::FinishSpawningActor(BlockActor, trans);
		
	}*/

}