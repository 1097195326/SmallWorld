#include "UIControllerManager.h"



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
UIControllerInterface * UIControllerManager::GetInternalUIController()
{
	return CurrentUIController;
}