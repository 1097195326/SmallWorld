#include "UIControllerManager.h"



UIControllerManager::UIControllerManager()
{
	CurrentUIController = nullptr;


}
void UIControllerManager::ChangeUIController(UIControllerIndex  ToIndex)
{
	UIControllerInterface * WantToController = nullptr;
	if (LoadedControllers.Contains(ToIndex))
	{
		WantToController = LoadedControllers[ToIndex];
	}
	else
	{
		switch (ToIndex)
		{
		case MainViewUIControllerIndex:
			WantToController = new MainViewUIController();
			LoadedControllers.Add(MainViewUIControllerIndex, WantToController);
			break;
		default:
			break;
		}
	}
	if (CurrentUIController == WantToController)
	{
		return;
	}
	if (CurrentUIController != nullptr)
	{
		CurrentUIController->Exit();
	}
	CurrentUIController = WantToController;
	CurrentUIController->Enter();
}
