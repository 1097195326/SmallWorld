#pragma once


#include "Templates/SingleTemplate.h"
#include "UIControllerInterface.h"


class UIControllerManager : public SingleTemplate<UIControllerManager>
{
public:
	UIControllerManager();

	void		ChangeUIController(UIControllerInterface * UIController);

	UIControllerInterface * GetUIController();

private:

	UIControllerInterface *	CurrentUIController;
};