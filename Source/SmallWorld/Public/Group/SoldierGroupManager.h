#pragma once
#include "SoldierGroup.h"


class SoldierGroupManager
{
public:
	static SoldierGroupManager * GetInstance();



protected:

private:
	SoldierGroupManager();


	list<SoldierGroup*>  mSoldierGroups;

};