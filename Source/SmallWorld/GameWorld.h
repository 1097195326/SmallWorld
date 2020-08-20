#pragma once

#include "SmallWorldInstance.h"
#include "GameWorldActor.h"

class ASoldierPawn;
class ABaseBuildingActor;

enum	DirectionEnum
{
	Direction_Up,
	Direction_Down,
	Direction_Left,
	Direction_Right,
};


class GameWorld : public SingleTemplateClass<GameWorld>
{
public:
	GameWorld();
	~GameWorld();

	
	void					BuildTileWorld();
	void					Update();

private:
	

	AGameWorldActor *		GameWorldActor;

	bool					IsInitialized;
	bool					IsPaused;


};