#pragma once

#include "SoldierBaseState.h"

class SoldierReadyState : public SoldierBaseState
{
public:
	SoldierReadyState(ASoldierPawn * _soldier);
	~SoldierReadyState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

};