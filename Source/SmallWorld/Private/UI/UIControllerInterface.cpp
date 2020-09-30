#include "UIControllerInterface.h"


void UIControllerInterface::InitControllerView()
{

}
void UIControllerInterface::Enter()
{
	InitControllerView();
	User_GameClient->AddViewportWidgetContent(ControllerView.ToSharedRef());
	OnEnter();
}
void UIControllerInterface::Exit()
{
	if (ControllerView.IsValid())
	{
		OnExit();
		User_GameClient->RemoveViewportWidgetContent(ControllerView.ToSharedRef());
	}
}