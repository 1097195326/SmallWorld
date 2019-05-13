#pragma once

#include "SoldierBaseState.h"

class SoldierMoveToGroupState : public SoldierBaseState
{
public:
	SoldierMoveToGroupState(ASoldierPawn * _soldier);
	~SoldierMoveToGroupState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

};