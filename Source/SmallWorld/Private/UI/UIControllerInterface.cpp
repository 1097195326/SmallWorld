#include "UIControllerInterface.h"


void UIControllerInterface::InitControllerView()
{

}
void UIControllerInterface::Enter()
{
	InitControllerView();
	GVC->AddViewportWidgetContent(ControllerView.ToSharedRef());
}
void UIControllerInterface::Exit()
{
	if (ControllerView.IsValid())
	{
		GVC->RemoveViewportWidgetContent(ControllerView.ToSharedRef());
	}
}