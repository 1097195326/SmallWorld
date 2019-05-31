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
	int indexInGroup = mAllSoldier.size() + 1;
	
	_soldier->SetGroupAndIndex(this, indexInGroup);
	

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
		FormationInfo info = GetFormationInfo(_formation->GetFormationType());
		mGroupLenth = info.Formation_L * info.Offset_Y;
		mGroupWidth = info.Formation_W * info.Offset_X;
		mCurrrentFormation->CalculateOffSet(info);
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
void SoldierGroup::ChangeStateIndex(GroupStateIndex _index)
{
	mStateIndex = _index;
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
FVector SoldierGroup::GetGroupLocation()
{
	return mGroupLocation;
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
		case e_SquareRectFormation:
			info.Formation_W = Archer_SquareFormation_W;
			info.Formation_L = Archer_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = Archer_HorizonalFormation_W;
			info.Formation_L = Archer_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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
		case e_SquareRectFormation:
			info.Formation_W = Footman_SquareFormation_W;
			info.Formation_L = Footman_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = Footman_HorizonalFormation_W;
			info.Formation_L = Footman_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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
		case e_SquareRectFormation:
			info.Formation_W = Griffin_SquareFormation_W;
			info.Formation_L = Griffin_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = Griffin_HorizonalFormation_W;
			info.Formation_L = Griffin_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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
		case e_SquareRectFormation:
			info.Formation_W = Horseman_SquareFormation_W;
			info.Formation_L = Horseman_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = Horseman_HorizonalFormation_W;
			info.Formation_L = Horseman_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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
		case e_SquareRectFormation:
			info.Formation_W = Knight_SquareFormation_W;
			info.Formation_L = Knight_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = Knight_HorizonalFormation_W;
			info.Formation_L = Knight_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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
		case e_SquareRectFormation:
			info.Formation_W = Mage_SquareFormation_W;
			info.Formation_L = Mage_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = Mage_HorizonalFormation_W;
			info.Formation_L = Mage_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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
		case e_SquareRectFormation:
			info.Formation_W = SiegeEngine_SquareFormation_W;
			info.Formation_L = SiegeEngine_SquareFormation_L;
			break;
		case e_HorizonalRectFormation:
			info.Formation_W = SiegeEngine_HorizonalFormation_W;
			info.Formation_L = SiegeEngine_HorizonalFormation_L;
			break;
		case e_VerticalRectFormation:
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