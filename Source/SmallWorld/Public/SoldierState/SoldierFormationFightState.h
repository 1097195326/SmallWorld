#pragma once

#include "SoldierBaseState.h"

class SoldierFormationFightState : public SoldierBaseState
{
public:
	SoldierFormationFightState(ASoldierPawn * _soldier);
	~SoldierFormationFightState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

};