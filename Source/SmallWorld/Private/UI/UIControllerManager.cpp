#include "UIControllerManager.h"
#include "MainViewUIController.h"



UIControllerManager::UIControllerManager()
{
	CurrentUIController = nullptr;


}
void UIControllerManager::ChangeUIController(UIControllerInterface * UIController)
{
	if (CurrentUIController == UIController)
	{
		return;
	}
	if (CurrentUIController != nullptr)
	{
		CurrentUIController->Exit();
	}
	CurrentUIController = UIController;
	CurrentUIController->Enter();
}
UIControllerInterface * UIControllerManager::GetUIController()
{
	return CurrentUIController;
}