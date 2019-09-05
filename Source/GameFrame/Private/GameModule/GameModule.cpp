//#include "GCore.h"
#include "GameModule.h"



void GameModule::SetUIController(UIController * _uiController)
{
	if (m_CurrentUIController)
	{
		m_CurrentUIController->HideView();
	}
	if (_uiController)
	{
		m_CurrentUIController = _uiController;
		m_CurrentUIController->ShowView();
	}
	else
	{
		m_CurrentUIController = nullptr;
	}
}
UIController * GameModule::GetCurrentUIController()
{
	return m_CurrentUIController;
}