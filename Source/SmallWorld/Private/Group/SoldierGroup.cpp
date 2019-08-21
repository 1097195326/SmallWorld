#include "SoldierGroup.h"
#include "SoldierGroupManager.h"
#include "GroupWaitingState.h"
#include "GroupAutoFightState.h"
#include "GroupFightState.h"
#include "GroupReadyState.h"

#include "CircleFormation.h"
#include "ConeFormation.h"
#include "RectFormation.h"



SoldierGroup::SoldierGroup():mGroupType(G_None)
{
	mGroupMaxNum = 12;
	mCurrrentFormation = nullptr;
	mCurrentState = nullptr;
	mEnemyGroup = nullptr;
	mIsPendingKill = false;

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
	for (auto mapIter : mGroupStateMap)
	{
		delete mapIter.second;
	}
	mGroupStateMap.clear();

}
void SoldierGroup::On_GameUpdate()
{
	for (auto soldier : mAllSoldier)
	{
		soldier->On_GameUpdate();
	}
}
bool SoldierGroup::AddSoldierToGroup(ASoldierPawn * _soldier)
{
	if (_soldier == nullptr)
	{
		return false;
	}
	if (mIsFull)
	{
		return false;
	}
	int indexInGroup = mAllSoldier.size() + 1;
	
	_soldier->SetGroupAndIndex(this, indexInGroup);
	

	ChangeSoldierState(_soldier);
	mAllSoldier.push_back(_soldier);
	if (mAllSoldier.size() == mGroupMaxNum)
	{
		mIsFull = true;
	}
	return true;
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
		mCurrrentFormation = nullptr;
	}
	if (_formation)
	{
		mCurrrentFormation = _formation;
		mGroupLenth = mCurrrentFormation->GetFormationInfo().Formation_L * mCurrrentFormation->GetFormationInfo().Offset_Y;
		mGroupWidth = mCurrrentFormation->GetFormationInfo().Formation_W * mCurrrentFormation->GetFormationInfo().Offset_X;
	}
}
void SoldierGroup::ChangeGroupState(GroupBaseState * _groupState)
{
	if (mCurrentState)
	{
		mCurrentState->OnEnd();
		mCurrentState = nullptr;
	}
	if (_groupState)
	{
		mCurrentState = _groupState;
		mCurrentState->OnEnter();
	}
}
void SoldierGroup::ChangeFormationByIndex(const FormationSpace::FormationType & formationIndex)
{
	std::map<FormationSpace::FormationType, BaseFormation*>::iterator  formationIter = mGroupFormationMap.find(formationIndex);
	if (formationIter != mGroupFormationMap.end())
	{
		ChangeFormation(formationIter->second);
	}
	else
	{
		BaseFormation * AddFormation = nullptr;
		switch (formationIndex)
		{
		case CircleFormationType:
			AddFormation = new  CircleFormation();
			break;
		case ConeFormationType:
			AddFormation = new  ConeFormation();
			break;
		case SquareRectFormationType:
			AddFormation = new  RectFormation();
			break;
		case HorizonalRectFormationType:
			AddFormation = new  RectFormation();
			break;
		case VerticalRectFormationType:
			AddFormation = new  RectFormation();
			break;
		default:
			break;
		}
		if (AddFormation)
		{
			FormationInfo info = GetFormationInfo(AddFormation->GetFormationType());
			AddFormation->CalculateOffSet(info);

			mGroupFormationMap.insert(std::pair<FormationSpace::FormationType, BaseFormation*>(formationIndex, AddFormation));
			ChangeFormation(AddFormation);
		}
	}
}
void SoldierGroup::ChangeGrouyStateByIndex(const GroupStateIndex & _index)
{
	std::map<GroupStateIndex, GroupBaseState*>::iterator  StateIter = mGroupStateMap.find(_index);
	if (StateIter != mGroupStateMap.end())
	{
		ChangeGroupState(StateIter->second);
	}
	else
	{
		GroupBaseState * AddState = nullptr;
		switch (_index)
		{
		case I_AutoFightIndex:
			AddState = new  GroupAutoFightState(this);
			break;
		case I_FightIndex:
			AddState = new  GroupFightState(this);
			break;
		case I_ReadyIndex:
			AddState = new  GroupReadyState(this);
			break;
		case I_WaitingIndex:
			AddState = new  GroupWaitingState(this);
			break;
		default:
			break;
		}
		if (AddState)
		{
			mGroupStateMap.insert(std::pair<GroupStateIndex, GroupBaseState*>(_index, AddState));
			ChangeGroupState(AddState);
		}
	}
}
void SoldierGroup::ChangeSoldierState(ASoldierPawn * _soldier)
{
	if (!mCurrentState)
	{
		return;
	}
	switch (mCurrentState->GetStateIndex())
	{
	case  I_AutoFightIndex:
	{
		_soldier->ChangeSoldierState(SoldierState::S_FightSelf);
		break;
	}
	case I_FightIndex:
	{
		if (mCurrrentFormation)
		{
			_soldier->ChangeSoldierState(SoldierState::S_FormationFight);
		}
		else
		{
			_soldier->ChangeSoldierState(SoldierState::S_FightSelf);
		}
		break;
	}
	case  I_ReadyIndex:
	{
		_soldier->ChangeSoldierState(SoldierState::S_FormationDefense);
		break;
	}
	case I_WaitingIndex:
	{
		_soldier->ChangeSoldierState(SoldierState::S_MoveToGroup);
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
void SoldierGroup::GroupBehaviorActions()
{

}
bool SoldierGroup::SearchEnemyGroup()
{
	SoldierGroup * enemyGroup = mGroupManager->GetEnemyGroupManager()->GetNearestGroupToLocation(GetGroupCenter());
	if (enemyGroup)
	{
		mEnemyGroup = enemyGroup;
		return true;
	}
	return false;
}
void SoldierGroup::MoveToForward()
{

}
void SoldierGroup::AttackEnemyGroup()
{

}

void SoldierGroup::SetGroupIndexAndLocationAndForward(int32 _index, FVector _location,FVector _forward)
{
	mIndexInManger = _index;
	mGroupLocation = _location;
	mGroupForward = _forward;
}
FVector SoldierGroup::GetSoldierLocationByIndex(int _index)
{
	FTransform tran(mGroupForward.Rotation(),mGroupLocation);
	return tran.TransformPosition(mCurrrentFormation->GetLocationByIndex(_index));
	//return mGroupLocation + mCurrrentFormation->GetLocationByIndex(_index);
}
FVector SoldierGroup::GetGroupCenter()
{

	return mGroupLocation;
}
FVector SoldierGroup::GetGroupLocation()
{
	return mGroupLocation;
}
FVector SoldierGroup::GetGroupForward()
{
	return mGroupForward;
}
int32 SoldierGroup::GetGroupIndex()
{
	return mIndexInManger;
}
FormationInfo SoldierGroup::GetFormationInfo(FormationType _type)
{
	FormationInfo info;
	switch (mGroupType)
	{
	case G_ArcherGroup:
	{
		info.Offset_X = Archer_FormationBoundX;
		info.Offset_Y = Archer_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = Archer_SquareFormation_W;
			info.Formation_L = Archer_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = Archer_HorizonalFormation_W;
			info.Formation_L = Archer_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = Archer_VerticalFormation_W;
			info.Formation_L = Archer_VerticalFormation_L;
			break;
		}
	}
	break;
	case G_FootmanGroup:
		info.Offset_X = Footman_FormationBoundX;
		info.Offset_Y = Footman_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = Footman_SquareFormation_W;
			info.Formation_L = Footman_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = Footman_HorizonalFormation_W;
			info.Formation_L = Footman_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = Footman_VerticalFormation_W;
			info.Formation_L = Footman_VerticalFormation_L;
			break;
		}
		break;
	case G_GriffinGroup:
		info.Offset_X = Griffin_FormationBoundX;
		info.Offset_Y = Griffin_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = Griffin_SquareFormation_W;
			info.Formation_L = Griffin_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = Griffin_HorizonalFormation_W;
			info.Formation_L = Griffin_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = Griffin_VerticalFormation_W;
			info.Formation_L = Griffin_VerticalFormation_L;
			break;
		}
		break;
	case G_HorsemanGroup:
		info.Offset_X = Horseman_FormationBoundX;
		info.Offset_Y = Horseman_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = Horseman_SquareFormation_W;
			info.Formation_L = Horseman_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = Horseman_HorizonalFormation_W;
			info.Formation_L = Horseman_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = Horseman_VerticalFormation_W;
			info.Formation_L = Horseman_VerticalFormation_L;
			break;
		}
		break;
	case G_KnightGroup:
		info.Offset_X = Knight_FormationBoundX;
		info.Offset_Y = Knight_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = Knight_SquareFormation_W;
			info.Formation_L = Knight_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = Knight_HorizonalFormation_W;
			info.Formation_L = Knight_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = Archer_VerticalFormation_W;
			info.Formation_L = Archer_VerticalFormation_L;
			break;
		}
		break;
	case G_MageGroup:
		info.Offset_X = Mage_FormationBoundX;
		info.Offset_Y = Mage_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = Mage_SquareFormation_W;
			info.Formation_L = Mage_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = Mage_HorizonalFormation_W;
			info.Formation_L = Mage_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = Mage_VerticalFormation_W;
			info.Formation_L = Mage_VerticalFormation_L;
			break;
		}
		break;
	case G_SiegeEngineGroup:
		info.Offset_X = SiegeEngine_FormationBoundX;
		info.Offset_Y = SiegeEngine_FormationBoundY;
		switch (_type)
		{
		case SquareRectFormationType:
			info.Formation_W = SiegeEngine_SquareFormation_W;
			info.Formation_L = SiegeEngine_SquareFormation_L;
			break;
		case HorizonalRectFormationType:
			info.Formation_W = SiegeEngine_HorizonalFormation_W;
			info.Formation_L = SiegeEngine_HorizonalFormation_L;
			break;
		case VerticalRectFormationType:
			info.Formation_W = SiegeEngine_VerticalFormation_W;
			info.Formation_L = SiegeEngine_VerticalFormation_L;
			break;
		}
		break;
	default:
		break;
	}
	return std::move(info);
}

void SoldierGroup::SetGroupType(SoldierType _soldierType)
{
	switch (_soldierType)
	{
	case S_Archer:
		mGroupType = G_ArcherGroup;
		mGroupMaxNum = ArcherGroupMaxNum;
		break;
	case S_Footman:
		mGroupType = G_FootmanGroup;
		mGroupMaxNum = FootmanGroupMaxNum;
		break;
	case S_Griffin:
		mGroupType = G_GriffinGroup;
		mGroupMaxNum = GriffinGroupMaxNum;
		break;
	case S_Horseman:
		mGroupType = G_HorsemanGroup;
		mGroupMaxNum = HorsemanGroupMaxNum;
		break;
	case S_Knight:
		mGroupType = G_KnightGroup;
		mGroupMaxNum = KnightGroupMaxNum;
		break;
	case S_Mage:
		mGroupType = G_MageGroup;
		mGroupMaxNum = MageGroupMaxNum;
		break;
	case S_SiegeEngine:
		mGroupType = G_SiegeEngineGroup;
		mGroupMaxNum = SiegeEngineGroupMaxNum;
		break;
	default:
		break;
	}
}
void SoldierGroup::SetSoldierGroupManager(SoldierGroupManager * _groupManager)
{
	mGroupManager = _groupManager;
}