#pragma once
#include "SoldierGroup.h"


class SoldierGroupManager
{
public:
	static SoldierGroupManager * GetInstance();
	SoldierGroupManager();

	void					PushSoldierToGroup(ASoldierPawn * _soldier);

	bool					IsFull();
	void					ClearSoldierGroups();
protected:

private:

	SoldierGroup *			mCurrentGroup;
	list<SoldierGroup*>		mSoldierGroups;

	int32					mGroupMaxNum;
};