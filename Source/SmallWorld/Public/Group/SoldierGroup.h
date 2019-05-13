#pragma once
#include "BaseGroup.h"
#include "SoldierPawn.h"
#include "GroupBaseState.h"



enum GroupType
{
	G_None,
	G_ArcherGroup,
	G_FootmanGroup,
	G_GriffinGroup,
	G_HorsemanGroup,
	G_KnightGroup,
	G_MageGroup,
	G_SiegeEngineGroup,
};
class SoldierGroup : public BaseGroup
{

public:
	SoldierGroup();
	~SoldierGroup();

	void					SetGroupType(SoldierType _soldierType);
	
	void					AddSoldierToGroup(ASoldierPawn * soldier);
	void					RemoveSoldierFromGroup(ASoldierPawn * soldier);
	list<ASoldierPawn*>		GetAllSoldier();
	
	void					ChangeFormation(BaseFormation * formation);
	void					ChangeGroupState(GroupBaseState * _groupState);
	void					ChangeStateIndex(GroupStateIndex _index);
	void					UpdateSoldierState();

protected:
	//void					
	void					ChangeSoldierState(ASoldierPawn * _soldier);

	GroupStateIndex				mStateIndex;
	GroupBaseState *			mCurrentState;
	BaseFormation *				mCurrrentFormation;

	GroupType					mGroupType;

	std::list<ASoldierPawn*>	mAllSoldier;
private:
	
};