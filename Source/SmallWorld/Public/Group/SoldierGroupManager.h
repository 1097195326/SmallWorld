#pragma once
#include "SoldierGroup.h"


class SoldierGroupManager
{
public:
	static SoldierGroupManager * GetInstance();


	void					PushSoldierToGroup(ASoldierPawn * _soldier);

	bool					IsFull();
	void					ClearSoldierGroups();
protected:

private:
	SoldierGroupManager();

	SoldierGroup *			mCurrentGroup;
	list<SoldierGroup*>		mSoldierGroups;

	int32					mGroupNum;
};