#pragma once

#include "CoreMinimal.h"
#include "SlateStyles/GameStyle.h"
#include "UnrealEd/Public/ObjectTools.h"
#include "UnrealEd/Public/Tests/AutomationEditorCommon.h"
#include "UserViewportClient.h"
#include "UnrealEd/Public/ClassIconFinder.h"
#include "SlateCore/Public/Styling/SlateIconFinder.h"



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