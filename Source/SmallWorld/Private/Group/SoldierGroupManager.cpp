#include "SoldierGroupManager.h"


SoldierGroupManager::SoldierGroupManager()
{
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
			mCurrentGroup->SetGroupLocation(mOrigin);
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
	return mSoldierGroups.size() == AllGroupMaxNum;
}
void SoldierGroupManager::SetOriginAndForward(FVector _origin, FVector _forward)
{
	mOrigin = _origin;
	mNormalForward = _forward;
	for (int i = 0; i < AllGroupMaxNum; i++)
	{
		
	}

}