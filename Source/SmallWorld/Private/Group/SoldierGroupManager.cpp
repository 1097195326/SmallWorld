#include "SoldierGroupManager.h"
#include "RectFormation.h"

SoldierGroupManager::SoldierGroupManager()
{
	mCurrentGroup = nullptr;

}
SoldierGroupManager * SoldierGroupManager::GetInstance()
{
	static SoldierGroupManager manger;
	return &manger;
}
void SoldierGroupManager::On_GameUpdate()
{
	for (auto group : mSoldierGroups)
	{
		group->On_GameUpdate();
	}
}
void SoldierGroupManager::PushSoldierToGroup(ASoldierPawn * _soldier)
{
	if (!IsFull())
	{
		if (mCurrentGroup == nullptr)
		{
			mCurrentGroup = new SoldierGroup();
			mCurrentGroup->SetGroupType(_soldier->mSoldierType);	
			mCurrentGroup->ChangeFormation(new RectFormation());
			int GroupNum = mSoldierGroups.size();
			mCurrentGroup->SetGroupIndexAndLocation(GroupNum, mGroupLocationMap[GroupNum]);
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
	mStartOrigin = _origin;
	mNormalForward = _forward;
	mPrepareOrigin = _origin + mNormalForward * GroupSize;

	for (int i = 0; i < AllGroupMaxNum; i++)
	{
		mGroupLocationMap[i] = mStartOrigin + -mNormalForward * i;
	}

}