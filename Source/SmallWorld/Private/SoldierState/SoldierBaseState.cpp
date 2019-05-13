#include "SoldierBaseState.h"


SoldierBaseState::SoldierBaseState(ASoldierPawn * _soldier) :mSoldier(_soldier)
{

}
SoldierBaseState::~SoldierBaseState()
{
	mSoldier = nullptr;

}
void SoldierBaseState::OnEnter()
{

}
void SoldierBaseState::OnProcess()
{

}
void SoldierBaseState::OnEnd()
{

}