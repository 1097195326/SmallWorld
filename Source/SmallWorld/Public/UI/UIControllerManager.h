#pragma once


#include "Templates/SingleTemplate.h"
#include "UIControllerInterface.h"


class UIControllerManager : public SingleTemplate<UIControllerManager>
{
public:
	void		ChangeUIController(UIControllerInterface * UIController);

	UIControllerInterface * GetUIController();
private:
	UIControllerManager();

	UIControllerInterface *	CurrentUIController;
};