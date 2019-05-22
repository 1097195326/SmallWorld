#pragma once
#include "SoldierGroup.h"


class SoldierGroupManager : public GObject
{
public:
	static SoldierGroupManager * GetInstance();
	SoldierGroupManager();

	virtual	void			On_GameUpdate() override;

	void					PushSoldierToGroup(ASoldierPawn * _soldier);

	bool					IsFull();
	void					ClearSoldierGroups();

	void					SetOriginAndForward(FVector _origin,FVector _forward);

protected:

private:
	map<int32, FVector>		mGroupLocationMap;

	FVector					mPrepareOrigin;
	FVector					mStartOrigin;
	FVector					mNormalForward;

	SoldierGroup *			mCurrentGroup;
	list<SoldierGroup*>		mSoldierGroups;

};