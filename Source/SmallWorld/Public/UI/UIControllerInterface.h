#pragma once

#include "CoreMinimal.h"
#include "SlateStyles/GameStyle.h"
#include "UnrealEd/Public/ObjectTools.h"
#include "UnrealEd/Public/Tests/AutomationEditorCommon.h"
#include "UserViewportClient.h"
#include "UnrealEd/Public/ClassIconFinder.h"
#include "SlateCore/Public/Styling/SlateIconFinder.h"
#include "Framework/Application/SlateApplication.h"



class UIControllerInterface
{
public:
	enum Type
	{
		T_None,
		T_NineGrid,
	};
	
	virtual void			InitControllerView();
	virtual void			Enter();
	virtual void			Exit();

	virtual ~UIControllerInterface(){}

	TSharedPtr<SOverlay>		GetControllerView() { return ControllerView; }

protected:
	TSharedPtr<SOverlay>		ControllerView;
	Type					ControllerType;

};