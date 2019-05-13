#pragma once

#include "SoldierBaseState.h"

class SoldierMoveToCityState : public SoldierBaseState
{
public:
	SoldierMoveToCityState(ASoldierPawn * _soldier);
	~SoldierMoveToCityState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

};