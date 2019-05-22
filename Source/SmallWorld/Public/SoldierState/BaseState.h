#pragma once
#include "GObject.h"


class BaseState : public GObject
{
public:

	virtual ~BaseState();

	virtual void OnEnter() = 0;
	virtual void OnProcess() = 0;
	virtual void OnEnd() = 0;

};