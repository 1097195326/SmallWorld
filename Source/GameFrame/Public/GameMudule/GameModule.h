#pragma once

#include "GObject.h"
#include "UIController.h"

class GAMEFRAME_API GameModule : public GObject
{
private:

protected:

	UIController * m_CurrentUIController;

	void SetUIController(UIController * _uiController);

public:
	

	UIController * GetCurrentUIController();
};
