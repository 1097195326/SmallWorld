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
void GameWorld::InitWithGameInstance(USmallWorldInstance * _GameInstance)
{
	mGameInstance = _GameInstance;
}
void GameWorld::BuildWorld()
{
	FTransform trans;
	ABlockActor * BlockActor = Cast<ABlockActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(mGameInstance, ABlockActor::StaticClass(), trans));
	if (BlockActor)
	{

		UGameplayStatics::FinishSpawningActor(BlockActor, trans);
		BlockActor->SetMesh();
	}

}