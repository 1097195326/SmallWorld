#pragma once

#include "SoldierBaseState.h"

class SoldierFightSelfState : public SoldierBaseState
{
public:
	SoldierFightSelfState(ASoldierPawn * _soldier);
	~SoldierFightSelfState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

};