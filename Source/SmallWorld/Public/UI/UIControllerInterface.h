#pragma once

#include "CoreMinimal.h"
#include "SOverlay.h"
#include "SWidget.h"

#include "UserViewportClient.h"


class UIControllerInterface
{
public:
	enum Type
	{
		T_None,
		T_NineGrid,
	};
	
	virtual void			InitControllerView() = 0;
	virtual void			Enter() = 0;
	virtual void			Exit() = 0;

	virtual ~UIControllerInterface(){}

	TSharedPtr<SOverlay>		GetControllerView() { return ControllerView; }

protected:
	TSharedPtr<SOverlay>		ControllerView;
	Type					ControllerType;

};