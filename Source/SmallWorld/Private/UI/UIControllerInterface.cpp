#include "UIControllerInterface.h"


void UIControllerInterface::InitControllerView()
{

}
void UIControllerInterface::Enter()
{
	InitControllerView();
	GVC->AddViewportWidgetContent(ControllerView.ToSharedRef());
	OnEnter();
}
void UIControllerInterface::Exit()
{
	if (ControllerView.IsValid())
	{
		OnExit();
		GVC->RemoveViewportWidgetContent(ControllerView.ToSharedRef());
	}
}