#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"



GameWorld::GameWorld()
{
	IsInitialized = false;

}
GameWorld::~GameWorld()
{
	ClearGeneralGoals();
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

	IsInitialized = true;
}
void GameWorld::ClearGeneralGoals()
{
	for (int i = 0; i < GeneralGoals.size(); i++)
	{
		GeneralGoal * goal = GeneralGoals[i];
		delete goal;
	}
	GeneralGoals.clear();

}
ACityActor *  GameWorld::BuildCity(int _x, int _y)
{
	FTransform trans(FVector(_x * CitySize * TitleSize + (CitySize * TitleSize * 0.5), _y * CitySize * TitleSize + (CitySize * TitleSize * 0.5), 0));
	ACityActor * CityActor = Cast<ACityActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ACityActor::StaticClass(), trans));
	if (CityActor)
	{
		CityActor->InitData(new CityData());
		CityActor->SetIndex(BuildingIndex(_x, _y));


		UGameplayStatics::FinishSpawningActor(CityActor, trans);
		
		GeneralGoal * goal = new GeneralGoal();
		goal->InitWithCityActor(CityActor);
		GeneralGoals.push_back(goal);

		return CityActor;
	}
	return nullptr;
}
void GameWorld::Update()
{
	if (IsInitialized)
	{
		for (auto Goal : GeneralGoals)
		{
			if (Goal->GetState() == e_UnActive)
			{
				Goal->Enter();
			}
			else
			{
				Goal->Process();
			}
		}
	}
}
bool GameWorld::IsInWorld(int _index)
{
	return _index >= BoundSize && _index <= WorldSize;
}
