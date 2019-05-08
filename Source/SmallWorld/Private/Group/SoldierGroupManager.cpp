#include "SoldierGroupManager.h"


SoldierGroupManager::SoldierGroupManager()
{

}
SoldierGroupManager * SoldierGroupManager::GetInstance()
{
	static SoldierGroupManager manger;
	return &manger;
}