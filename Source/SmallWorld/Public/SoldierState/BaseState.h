#pragma once


class BaseState
{
public:

	virtual ~BaseState();

	virtual void OnEnter() = 0;
	virtual void OnProcess() = 0;
	virtual void OnEnd() = 0;

};