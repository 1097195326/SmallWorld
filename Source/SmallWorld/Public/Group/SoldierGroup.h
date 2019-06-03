#pragma once
#include "BaseGroup.h"
#include "SoldierPawn.h"
#include "GroupBaseState.h"

#include "GameConfig.h"



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
	virtual void			On_GameUpdate() override;

	void					SetGroupType(SoldierType _soldierType);
	
	void					AddSoldierToGroup(ASoldierPawn * soldier);
	void					RemoveSoldierFromGroup(ASoldierPawn * soldier);
	list<ASoldierPawn*>		GetAllSoldier();
	
	void					ChangeFormation(BaseFormation * formation);
	void					ChangeGroupState(GroupBaseState * _groupState);
	void					ChangeStateIndex(GroupStateIndex _index);
	void					UpdateSoldierState();
	
	float					GetGroupLength() { return mGroupLenth; }
	float					GetGroupWidth() { return mGroupWidth; }

	void					SetGroupIndexAndLocationAndForward(int32 _index, FVector _location, FVector _forward);

	FVector					GetSoldierLocationByIndex(int _index);

	FVector					GetGroupLocation();
	FVector					GetGroupForward();
	int32					GetGroupIndex();

protected:
	FormationInfo			GetFormationInfo(FormationType _type);
	void					ChangeSoldierState(ASoldierPawn * _soldier);

	GroupStateIndex				mStateIndex;
	GroupBaseState *			mCurrentState;
	BaseFormation *				mCurrrentFormation;

	GroupType					mGroupType;

	std::list<ASoldierPawn*>	mAllSoldier;

	
	FVector						mGroupLocation;
	FVector						mGroupForward;
	int32						mIndexInManger;

	float						mGroupLenth;
	float						mGroupWidth;
private:
	
};