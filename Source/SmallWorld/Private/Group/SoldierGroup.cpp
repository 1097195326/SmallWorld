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
	mAllSoldier.push_back(_soldier);
}
void SoldierGroup::RemoveSoldierFromGroup(ASoldierPawn * _soldier)
{
	mAllSoldier.remove(_soldier);
}
list<ASoldierPawn*> SoldierGroup::GetAllSoldier()
{
	return mAllSoldier;
}
void SoldierGroup::ChangeFormation(BaseFormation * formation)
{
	mCurrrentFormation = formation;
	mCurrrentFormation->CalculateOffSet(mAllSoldier);
}
void SoldierGroup::SetGroupType(SoldierType _soldierType)
{
	switch (_soldierType)
	{
	case S_Archer:
		mGroupType = G_ArcherGroup;
		mSoldierNum = 10;
		break;
	case S_Footman:
		mGroupType = G_FootmanGroup;
		mSoldierNum = 10;
		break;
	case S_Griffin:
		mGroupType = G_GriffinGroup;
		mSoldierNum = 10;
		break;
	case S_Horseman:
		mGroupType = G_HorsemanGroup;
		mSoldierNum = 10;
		break;
	case S_Knight:
		mGroupType = G_KnightGroup;
		mSoldierNum = 10;
		break;
	case S_Mage:
		mGroupType = G_MageGroup;
		mSoldierNum = 10;
		break;
	case S_SiegeEngine:
		mGroupType = G_SiegeEngineGroup;
		mSoldierNum = 10;
		break;
	default:
		break;
	}
}
bool SoldierGroup::IsFull()
{
	return mAllSoldier.size() == mSoldierNum;
}