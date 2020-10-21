#include "UIControllerInterface.h"


void UIControllerInterface::InitControllerView()
{

}
void UIControllerInterface::Enter()
{
	InitControllerView();
	if (ControllerView.IsValid())
	{
		User_GameClient->AddViewportWidgetContent(ControllerView.ToSharedRef());
	}
	OnEnter();
}
void UIControllerInterface::Exit()
{
	OnExit();
	if (ControllerView.IsValid())
	{
		User_GameClient->RemoveViewportWidgetContent(ControllerView.ToSharedRef());
	}
}