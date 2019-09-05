#pragma once
#include "GObject.h"


class GAMEFRAME_API UIController : public GObject
{
protected:
	
public:
	virtual void	InitView() {}
	virtual void	RefreshView() {}
	virtual void	ShowView(){}
	virtual void	HideView() {}
	virtual void	DestroyView(){}



};