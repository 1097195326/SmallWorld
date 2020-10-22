#include "UIControllerManager.h"



UIControllerManager::UIControllerManager()
{
	CurrentUIController = nullptr;
	PendingUIController = nullptr;

}
void UIControllerManager::Tick(float DeltaTime)
{
	if (PendingUIController != nullptr )
	{
		if (CurrentUIController)
		{
			if (CurrentUIController->CanSafeLevel())
			{
				CurrentUIController->Exit();
				CurrentUIController = PendingUIController;
				PendingUIController = nullptr;
				CurrentUIController->Enter();
			}
		}
		else
		{
			CurrentUIController = PendingUIController;
			PendingUIController = nullptr;
			CurrentUIController->Enter();
		}
	}
	if (CurrentUIController)
	{
		CurrentUIController->Tick(DeltaTime);
	}
	
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
		case LoadingViewUIControllerIndex:
			WantToController = new LoadingViewUIController();
			LoadedControllers.Add(LoadingViewUIControllerIndex, WantToController);
		case LoginViewUIControllerIndex:
			WantToController = new LoginViewUIController();
			LoadedControllers.Add(LoginViewUIControllerIndex, WantToController);
			break;
		case MainViewUIControllerIndex:
			WantToController = new MainViewUIController();
			LoadedControllers.Add(MainViewUIControllerIndex, WantToController);
			break;
		default:
			break;
		}
	}
	/*if (CurrentUIController == WantToController)
	{
		return;
	}*/
	/*if (CurrentUIController != nullptr)
	{
		CurrentUIController->Exit();
	}*/
	PendingUIController = WantToController;
	
}
