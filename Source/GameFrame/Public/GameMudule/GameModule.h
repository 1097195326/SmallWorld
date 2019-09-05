#pragma once

#include "BaseObject.h"
#include "UIController.h"

class GAMEFRAME_API GameModule : public BaseObject
{
private:

protected:

	UIController * m_CurrentUIController;

	void SetUIController(UIController * _uiController);

public:
	

	UIController * GetCurrentUIController();
};
