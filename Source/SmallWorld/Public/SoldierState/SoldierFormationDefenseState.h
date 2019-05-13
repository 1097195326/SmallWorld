#pragma once

#include "SoldierBaseState.h"

class SoldierFormationDefenseState : public SoldierBaseState
{
public:
	SoldierFormationDefenseState(ASoldierPawn * _soldier);
	~SoldierFormationDefenseState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

};