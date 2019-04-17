#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"



GameWorld::GameWorld()
{
	
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
void GameWorld::BuildWorld()
{
	// Build Gameworld Actor
	FTransform trans(FVector((WorldSize + BoundSize * 2) * CitySize * TitleSize * 0.5, (WorldSize + BoundSize * 2) * CitySize * TitleSize * 0.5, 0));
	GameWorldActor = Cast<AGameWorldActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AGameWorldActor::StaticClass(), trans));
	if (GameWorldActor)
	{
		UGameplayStatics::FinishSpawningActor(GameWorldActor, trans);
	}
	// Build Cities
	for (int x = 0; x < WorldSize + BoundSize * 2 ; x++)
	{
		if (IsInWorld(x))
		{
			vector<ACityActor*> CityList;
			for (int y = 0; y < WorldSize + BoundSize * 2; y++)
			{
				if (IsInWorld(y))
				{
					ACityActor * CityActor = BuildCity(x, y);
					if (CityActor)
					{
						CityList.push_back(CityActor);
					}
				}
				else
				{
					BuildCity(x, y);
				}
			}
			CityMap.push_back(CityList);
		}
		else
		{
			for (int y = 0; y < WorldSize + BoundSize * 2; y++)
			{
				BuildCity(x, y);
			}
		}
	}
}
ACityActor *  GameWorld::BuildCity(int _x, int _y)
{
	FTransform trans(FVector(_x * CitySize * TitleSize + (CitySize * TitleSize * 0.5), _y * CitySize * TitleSize + (CitySize * TitleSize * 0.5), 0));
	ACityActor * CityActor = Cast<ACityActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ACityActor::StaticClass(), trans));
	if (CityActor)
	{
		CityActor->SetIndex(FBuildingIndex(_x, _y));
		UGameplayStatics::FinishSpawningActor(CityActor, trans);
		
		return CityActor;
	}
	return nullptr;
}
bool GameWorld::IsInWorld(int _index)
{
	return _index >= BoundSize && _index <= WorldSize;
}