#include "SoldierGroup.h"

SoldierGroup::SoldierGroup():mGroupType(G_None)
{

}

void SoldierGroup::AddSoldierToGroup(ASoldierPawn * _soldier)
{
	if (_soldier == nullptr)
	{
		return;
	}
	if (mGroupType == G_None)
	{
		SetGroupType(_soldier->mSoldierType);
	}
	AllSoldier.push_back(_soldier);
}
void SoldierGroup::RemoveSoldierFromGroup(ASoldierPawn * _soldier)
{
	AllSoldier.remove(_soldier);
}
list<ASoldierPawn*> SoldierGroup::GetAllSoldier()
{
	return AllSoldier;
}
void SoldierGroup::ChangeFormation(BaseFormation * formation)
{
	CurrrentFormation = formation;
	CurrrentFormation->CalculateOffSet(AllSoldier);
}
void SoldierGroup::SetGroupType(SoldierType _soldierType)
{
	switch (_soldierType)
	{
	case S_Archer:
		mGroupType = G_ArcherGroup;
		mGroupNum = 10;
		break;
	case S_Footman:
		mGroupType = G_FootmanGroup;
		mGroupNum = 10;
		break;
	case S_Griffin:
		mGroupType = G_GriffinGroup;
		mGroupNum = 10;
		break;
	case S_Horseman:
		mGroupType = G_HorsemanGroup;
		mGroupNum = 10;
		break;
	case S_Knight:
		mGroupType = G_KnightGroup;
		mGroupNum = 10;
		break;
	case S_Mage:
		mGroupType = G_MageGroup;
		mGroupNum = 10;
		break;
	case S_SiegeEngine:
		mGroupType = G_SiegeEngineGroup;
		mGroupNum = 10;
		break;
	default:
		break;
	}
}