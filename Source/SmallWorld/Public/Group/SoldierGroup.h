#pragma once
#include "BaseGroup.h"
#include "SoldierPawn.h"
#include "GroupBaseState.h"

const int32 ArcherGroupMaxNum = 12;
const int32 FootmanGroupMaxNum = 12;
const int32 GriffinGroupMaxNum = 12;
const int32 HorsemanGroupMaxNum = 12;
const int32 KnightGroupMaxNum = 12;
const int32 MageGroupMaxNum = 12;
const int32 SiegeEngineGroupMaxNum = 12;

const int32 AllGroupMaxNum = 2;
const float GroupSize = 2500 * 3.f;
const float FormationSize = 2500 * 2.f;


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
	
	void					SetGroupIndexAndLocation(int32 _index, FVector _location);

	FVector					GetGroupLocation();
	int32					GetGroupIndex();

protected:
	//void					
	void					ChangeSoldierState(ASoldierPawn * _soldier);

	GroupStateIndex				mStateIndex;
	GroupBaseState *			mCurrentState;
	BaseFormation *				mCurrrentFormation;

	GroupType					mGroupType;

	std::list<ASoldierPawn*>	mAllSoldier;

	FVector						mGroupLocation;
	int32						mGroupIndex;
private:
	
};