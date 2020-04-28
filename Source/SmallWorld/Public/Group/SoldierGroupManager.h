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
	
	SoldierGroup *			GetCurrentGroup();
	void					SetCurrentGroup(SoldierGroup * temGroup);

	void					SetOriginAndForward(FVector _origin,FVector _forward);

	void					SetEnemyGroupManager(SoldierGroupManager * _enemyGroupManager);
	SoldierGroupManager *	GetEnemyGroupManager();
	SoldierGroup *			GetNearestGroupToLocation(FVector _location);

protected:
	SoldierGroup *			CreateGroupBySoldierType(ESoldierType _type);
private:
	SoldierGroupManager *	mEnemyGroupManager;

	map<int32, FVector>		mGroupLocationMap;

	FVector					mPrepareOrigin;
	FVector					mStartOrigin;
	FVector					mNormalForward;

	SoldierGroup *			mCurrentGroup;
	list<SoldierGroup*>		mSoldierGroups;

};