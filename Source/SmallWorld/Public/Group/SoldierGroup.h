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
protected:
	GroupType					mGroupType;
	int32						mGroupNum;

	std::list<ASoldierPawn*>	AllSoldier;
	BaseFormation *				CurrrentFormation;
public:
	SoldierGroup();

	void					SetGroupType(SoldierType _soldierType);
	void					AddSoldierToGroup(ASoldierPawn * soldier);
	void					RemoveSoldierFromGroup(ASoldierPawn * soldier);
	list<ASoldierPawn*>		GetAllSoldier();
	void					ChangeFormation(BaseFormation * formation);
public:


};