#include "SoldierGroup.h"
#include "GroupWaitingState.h"

#include "SoldierFightSelfState.h"
#include "SoldierFormationFightState.h"
#include "SoldierFormationDefenseState.h"
#include "SoldierMoveToGroupState.h"


SoldierGroup::SoldierGroup():mGroupType(G_None)
{
	mGroupMaxNum = 12;
	mCurrrentFormation = nullptr;
	mCurrentState = nullptr;

	ChangeGroupState(new GroupWaitingState(this));

}
SoldierGroup::~SoldierGroup()
{
	if (mCurrentState)
	{
		delete mCurrentState;
		mCurrentState = nullptr;
	}
	if (mCurrrentFormation)
	{
		delete mCurrrentFormation;
		mCurrrentFormation = nullptr;
	}

}
void SoldierGroup::On_GameUpdate()
{
	for (auto soldier : mAllSoldier)
	{
		soldier->On_GameUpdate();
	}
}
void SoldierGroup::AddSoldierToGroup(ASoldierPawn * _soldier)
{
	if (_soldier == nullptr)
	{
		return;
	}
	if (mIsFull)
	{
		return;
	}
	if (mGroupType == G_None)
	{
		SetGroupType(_soldier->mSoldierType);
	}
	_soldier->SetGroup(this);
	ChangeSoldierState(_soldier);
	mAllSoldier.push_back(_soldier);
	if (mAllSoldier.size() == mGroupMaxNum)
	{
		mIsFull = true;
	}
}
void SoldierGroup::RemoveSoldierFromGroup(ASoldierPawn * _soldier)
{
	SubGroupNum();
	mAllSoldier.remove(_soldier);
}
list<ASoldierPawn*> SoldierGroup::GetAllSoldier()
{
	return mAllSoldier;
}
void SoldierGroup::ChangeFormation(BaseFormation * _formation)
{
	if (mCurrrentFormation)
	{
		delete mCurrrentFormation;
		mCurrrentFormation = nullptr;
	}
	if (_formation)
	{
		mCurrrentFormation = _formation;
		mCurrrentFormation->CalculateOffSet(mAllSoldier);
	}
}
void SoldierGroup::ChangeGroupState(GroupBaseState * _groupState)
{
	if (mCurrentState)
	{
		mCurrentState->OnEnd();
		delete mCurrentState;
		mCurrentState = nullptr;
	}
	if (_groupState)
	{
		mCurrentState = _groupState;
		mCurrentState->OnEnter();
	}
}
void SoldierGroup::ChangeSoldierState(ASoldierPawn * _soldier)
{
	switch (mStateIndex)
	{
	case I_FightIndex:
	{
		if (mCurrrentFormation)
		{
			_soldier->ChangeSoldierState(new SoldierFormationFightState(_soldier));
		}
		else
		{
			_soldier->ChangeSoldierState(new SoldierFightSelfState(_soldier));
		}
		break;
	}
	case  I_ReadyIndex:
	{
		_soldier->ChangeSoldierState(new SoldierFormationDefenseState(_soldier));
		break;
	}
	case I_WaitingIndex:
	{
		_soldier->ChangeSoldierState(new SoldierMoveToGroupState(_soldier));
		break;
	}
	}
}
void SoldierGroup::UpdateSoldierState()
{
	for (auto soldier : mAllSoldier)
	{
		ChangeSoldierState(soldier);
	}
}
void SoldierGroup::ChangeStateIndex(GroupStateIndex _index)
{
	mStateIndex = _index;
}
void SoldierGroup::SetGroupIndexAndLocation(int32 _index, FVector _location)
{
	mGroupIndex = _index;
	mGroupLocation = _location;
}
FVector SoldierGroup::GetGroupLocation()
{
	return mGroupLocation;
}
int32 SoldierGroup::GetGroupIndex()
{
	return mGroupIndex;
}
void SoldierGroup::SetGroupType(SoldierType _soldierType)
{
	switch (_soldierType)
	{
	case S_Archer:
		mGroupType = G_ArcherGroup;
		break;
	case S_Footman:
		mGroupType = G_FootmanGroup;
		break;
	case S_Griffin:
		mGroupType = G_GriffinGroup;
		break;
	case S_Horseman:
		mGroupType = G_HorsemanGroup;
		break;
	case S_Knight:
		mGroupType = G_KnightGroup;
		break;
	case S_Mage:
		mGroupType = G_MageGroup;
		break;
	case S_SiegeEngine:
		mGroupType = G_SiegeEngineGroup;
		break;
	default:
		break;
	}
}