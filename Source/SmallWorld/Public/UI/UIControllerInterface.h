#pragma once

#include "CoreMinimal.h"
#include "GameConfig.h"
#include "SlateStyles/GameStyle.h"
#include "UserViewportClient.h"
#include "SlateCore/Public/Styling/SlateIconFinder.h"
#include "Framework/Application/SlateApplication.h"
#include "WrapActor.h"
#include "WrapCharacter.h"



class UIControllerInterface
{
public:
	enum Type
	{
		T_None,
		T_NineGrid,
	};
	
	virtual void	InitControllerView();
	virtual void	Enter() final;
	virtual void	Exit() final;
	virtual void	OnEnter(){}
	virtual void	OnExit(){}
	virtual void	Tick(float DeltaTime){}
	virtual void	SelectGameActor(AWrapActor * GameActorPtr) {}
	virtual void	SelectGameActor(AWrapCharacter * GameCharacterPtr) {}
	virtual bool	CanSafeLevel() { return true; }

	virtual ~UIControllerInterface(){}

	TSharedPtr<SOverlay>		GetControllerView() { return ControllerView; }

protected:
	TSharedPtr<SOverlay>		ControllerView;
	Type					ControllerType;

};