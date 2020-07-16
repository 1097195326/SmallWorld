#pragma once
#include "GameObjectClass.h"


class BaseState : public GameObjectClass
{
public:

	virtual ~BaseState();

	virtual void OnEnter() = 0;
	virtual void OnProcess() = 0;
	virtual void OnEnd() = 0;

};