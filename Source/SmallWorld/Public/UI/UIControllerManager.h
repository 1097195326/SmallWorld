#pragma once


#include "Templates/SingleTemplateClass.h"
#include "UIControllerInterface.h"
#include "MainViewUIController.h"
#include "LoginViewUIController.h"
#include "LoadingViewUIController.h"


class UIControllerManager : public SingleTemplateClass<UIControllerManager>
{
public:
	enum UIControllerIndex
	{
		LoadingViewUIControllerIndex,
		LoginViewUIControllerIndex,
		MainViewUIControllerIndex,

	};
	UIControllerManager();

	void Tick(float DeltaTime);

	void		ChangeUIController(UIControllerIndex  ToIndex);

	UIControllerInterface * GetUIController() { return CurrentUIController; }
	template<typename ControllerClass>
	ControllerClass * GetUIController()
	{
		return dynamic_cast<ControllerClass*>(GetUIController());
	}
protected:
	TMap<UIControllerIndex, UIControllerInterface*>   LoadedControllers;
	
	UIControllerInterface *	CurrentUIController;
	UIControllerInterface *	PendingUIController;
};

#define  GetUIControllerToType(ControllerClass) UIControllerManager::GetInstance()->GetUIController<ControllerClass>()
#define  GetCurrentUIController UIControllerManager::GetInstance()->GetUIController()