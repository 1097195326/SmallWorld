#pragma once


#include "Templates/SingleTemplate.h"
#include "UIControllerInterface.h"
#include "MainViewUIController.h"


class UIControllerManager : public SingleTemplate<UIControllerManager>
{
public:
	UIControllerManager();

	void		ChangeUIController(UIControllerInterface * UIController);

	UIControllerInterface * GetInternalUIController();

	template<typename ControllerClass>
	ControllerClass * GetUIController()
	{
		return (ControllerClass*)(GetInternalUIController());
	}

protected:

	UIControllerInterface *	CurrentUIController;
};

#define  GetUIController(ControllerClass) UIControllerManager::GetInstance()->GetUIController<ControllerClass>()