#pragma once
#include "BaseGroup.h"
#include "SoldierPawn.h"

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

	void					SetGroupType(SoldierType _soldierType);
	void					AddSoldierToGroup(ASoldierPawn * soldier);
	void					RemoveSoldierFromGroup(ASoldierPawn * soldier);
	list<ASoldierPawn*>		GetAllSoldier();
	void					ChangeFormation(BaseFormation * formation);
	bool					IsFull();
protected:
	GroupType					mGroupType;
	int32						mSoldierNum;

	std::list<ASoldierPawn*>	mAllSoldier;
	BaseFormation *				mCurrrentFormation;
private:


};