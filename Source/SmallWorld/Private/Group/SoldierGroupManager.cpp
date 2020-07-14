#include "SoldierGroupManager.h"
#include "RectFormation.h"
#include "CloseCombatGroup.h"
#include "CommandoGroup.h"
#include "DistantFightGroup.h"

SoldierGroupManager::SoldierGroupManager()
{
	mCurrentGroup = nullptr;
	mEnemyGroupManager = nullptr;

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
	/*if (!IsFull())
	{
		if (mCurrentGroup == nullptr)
		{
			mCurrentGroup = CreateGroupBySoldierType(_soldier->GetSoldierType());
			mCurrentGroup->SetSoldierGroupManager(this);
			mCurrentGroup->SetGroupType(_soldier->GetSoldierType());
			mCurrentGroup->ChangeFormationByIndex(SquareRectFormationType);
			int GroupNum = mSoldierGroups.size();
			mCurrentGroup->SetGroupIndexAndLocationAndForward(GroupNum, mGroupLocationMap[GroupNum],mNormalForward);
		}
		mCurrentGroup->AddSoldierToGroup(_soldier);
		if (mCurrentGroup->IsFull())
		{
			mSoldierGroups.push_back(mCurrentGroup);
			mCurrentGroup = nullptr;
		}
	}*/
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
void SoldierGroupManager::SetEnemyGroupManager(SoldierGroupManager * _enemyGroupManager)
{
	mEnemyGroupManager = _enemyGroupManager;
}
SoldierGroupManager * SoldierGroupManager::GetEnemyGroupManager()
{
	return mEnemyGroupManager;
}
SoldierGroup * SoldierGroupManager::CreateGroupBySoldierType(ESoldierType _type)
{
	SoldierGroup * resultGroup = nullptr;
	switch (_type)
	{
	case S_Knight:
	case S_Footman:
		resultGroup = new CloseCombatGroup();
		break;
	case S_Griffin:
	case S_Horseman:
		resultGroup = new CommandoGroup();
		break;
	case S_Archer:
	case S_Mage:
	case S_SiegeEngine:
		resultGroup = new DistantFightGroup();
		break;
	}
	return resultGroup;
}
SoldierGroup * SoldierGroupManager::GetNearestGroupToLocation(FVector _location)
{
	SoldierGroup * resultGroup = nullptr;
	float preDistance = FLT_MAX;
	for (SoldierGroup * soldierGroup : mSoldierGroups)
	{
		if (!soldierGroup->IsPendingKill())
		{
			float dis = FVector::DistSquaredXY(_location, soldierGroup->GetGroupLocation());
			if (dis < preDistance)
			{
				resultGroup = soldierGroup;
				preDistance = dis;
			}
		}
	}
	return resultGroup;
}
bool SoldierGroupManager::IsFull()
{
	return mSoldierGroups.size() == AllGroupMaxNum;
}
void SoldierGroupManager::SetOriginAndForward(FVector _origin, FVector _forward)
{
	mStartOrigin = _origin;
	mNormalForward = _forward;
	mPrepareOrigin = _origin + mNormalForward * 2500;

	for (int i = 0; i < AllGroupMaxNum; i++)
	{
		mGroupLocationMap[i] = mStartOrigin + mNormalForward * 2500 * (i + 1);
	}

}
SoldierGroup * SoldierGroupManager::GetCurrentGroup()
{
	return mCurrentGroup;
}
void SoldierGroupManager::SetCurrentGroup(SoldierGroup * temGroup)
{
	mCurrentGroup = temGroup;
}