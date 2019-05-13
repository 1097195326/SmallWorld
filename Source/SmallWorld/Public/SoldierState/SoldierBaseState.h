#pragma once

#include "BaseState.h"

class ASoldierPawn;

class SoldierBaseState : public BaseState
{
public:
	SoldierBaseState(ASoldierPawn * _soldier);
	~SoldierBaseState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

protected:
	ASoldierPawn * mSoldier;

private:

};