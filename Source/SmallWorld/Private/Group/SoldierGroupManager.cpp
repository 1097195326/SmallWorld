#include "SoldierGroupManager.h"


SoldierGroupManager::SoldierGroupManager()
{
	mGroupMaxNum = 2;
	mCurrentGroup = nullptr;

}
SoldierGroupManager * SoldierGroupManager::GetInstance()
{
	static SoldierGroupManager manger;
	return &manger;
}
void SoldierGroupManager::PushSoldierToGroup(ASoldierPawn * _soldier)
{
	if (!IsFull())
	{
		if (mCurrentGroup == nullptr)
		{
			mCurrentGroup = new SoldierGroup();
		}
		mCurrentGroup->AddSoldierToGroup(_soldier);
		if (mCurrentGroup->IsFull())
		{
			mSoldierGroups.push_back(mCurrentGroup);
			mCurrentGroup = nullptr;
		}
	}
}
void SoldierGroupManager::ClearSoldierGroups()
{
	for (auto soldierGroup : mSoldierGroups)
	{
		delete soldierGroup;
		soldierGroup = nullptr;
	}
	mSoldierGroups.clear();
}
bool SoldierGroupManager::IsFull()
{
	return mSoldierGroups.size() == mGroupMaxNum;
}