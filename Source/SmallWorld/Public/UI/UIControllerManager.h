#pragma once


#include "Templates/SingleTemplate.h"
#include "UIControllerInterface.h"
#include "MainViewUIController.h"

class UIControllerManager : public SingleTemplate<UIControllerManager>
{
public:
	enum UIControllerIndex
	{
		MainViewUIControllerIndex,

	};
	UIControllerManager();

	void		ChangeUIController(UIControllerIndex  ToIndex);

protected:
	UIControllerInterface * GetInternalUIController() { return CurrentUIController; }

	template<typename ControllerClass>
	ControllerClass * GetUIController()
	{
		return dynamic_cast<ControllerClass*>(GetInternalUIController());
	}

	TMap<UIControllerIndex, UIControllerInterface*>   LoadedControllers;
	
	UIControllerInterface *	CurrentUIController;
};

#define  GetUIController(ControllerClass) UIControllerManager::GetInstance()->GetUIController<ControllerClass>()