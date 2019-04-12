#include "GameWorld.h"


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

}