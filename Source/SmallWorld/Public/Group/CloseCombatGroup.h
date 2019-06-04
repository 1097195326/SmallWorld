#pragma once
#include "SoldierGroup.h"

class CloseCombatGroup : public SoldierGroup
{
public:
	virtual void			GroupBehaviorActions() override;
	virtual bool			SearchEnemyGroup() override;
	virtual void			MoveToForward() override;
	virtual void			AttackEnemyGroup() override;
};