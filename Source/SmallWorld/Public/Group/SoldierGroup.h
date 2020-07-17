#pragma once
#include "BaseGroup.h"
#include "BaseSoldierDataClass.h"
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

	void					SetSoldierGroupManager(class SoldierGroupManager * _groupManager);
	void					SetGroupType(SoldierTypeEnum _soldierType);

	bool					AddSoldierToGroup(ASoldierPawn * soldier);
	void					RemoveSoldierFromGroup(ASoldierPawn * soldier);
	list<ASoldierPawn*>		GetAllSoldier();
	
	void					ChangeFormationByIndex(const FormationSpace::FormationType & formationIndex);
	// Group State
	void					ChangeGrouyStateByIndex(const GroupStateIndex & _index);
	void					UpdateSoldierState();
	// behavior action
	virtual void			GroupBehaviorActions();
	virtual bool			SearchEnemyGroup();
	virtual void			MoveToForward();
	virtual void			AttackEnemyGroup();


	inline float			GetGroupLength() { return mGroupLenth; }
	inline float			GetGroupWidth() { return mGroupWidth; }

	void					SetGroupIndexAndLocationAndForward(int32 _index, FVector _location, FVector _forward);

	FVector					GetSoldierLocationByIndex(int _index);

	FVector					GetGroupCenter();
	FVector					GetGroupLocation();
	FVector					GetGroupForward();
	int32					GetGroupIndex();


	inline bool				IsPendingKill() { return mIsPendingKill; }
protected:
	void					ChangeGroupState(GroupBaseState * _groupState);
	void					ChangeFormation(BaseFormation * formation);

	FormationSpace::FormationInfo			GetFormationInfo(FormationSpace::FormationType _type);
	void					ChangeSoldierState(ASoldierPawn * _soldier);

	bool						mIsPendingKill;

	GroupBaseState *			mCurrentState;
	BaseFormation *				mCurrrentFormation;
	SoldierGroup *				mEnemyGroup;
	class SoldierGroupManager *	mGroupManager;

	GroupType					mGroupType;

	std::list<ASoldierPawn*>	mAllSoldier;
	std::map<GroupStateIndex, GroupBaseState*>		mGroupStateMap;
	std::map<FormationSpace::FormationType, BaseFormation*>		mGroupFormationMap;

	
	FVector						mGroupLocation;
	FVector						mGroupForward;
	int32						mIndexInManger;

	float						mGroupLenth;
	float						mGroupWidth;
private:
	
};