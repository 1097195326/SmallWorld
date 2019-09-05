#pragma once
#include "BaseObject.h"


class GAMEFRAME_API UIController : public BaseObject
{
protected:
	
public:
	virtual void	InitView() {}
	virtual void	RefreshView() {}
	virtual void	ShowView(){}
	virtual void	HideView() {}
	virtual void	DestroyView(){}



};