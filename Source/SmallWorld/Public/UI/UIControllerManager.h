#pragma once


#include "Templates/SingleTemplateClass.h"
#include "UIControllerInterface.h"
#include "MainViewUIController.h"
#include "LoginViewUIController.h"

class UIControllerManager : public SingleTemplateClass<UIControllerManager>
{
public:
	enum UIControllerIndex
	{
		LoginViewUIControllerIndex,
		MainViewUIControllerIndex,

	};
	UIControllerManager();

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
};

#define  GetUIControllerToType(ControllerClass) UIControllerManager::GetInstance()->GetUIController<ControllerClass>()
#define  GetCurrentUIController UIControllerManager::GetInstance()->GetUIController()