#include "MainViewUIController.h"



TSharedPtr<SWidget> MainViewUIController::MakeTopLeftWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeTopCenterWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeTopRightWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeMiddleLeftWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>		MainViewUIController::MakeMiddleCenterWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeMiddleRightWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomLeftWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomCenterWidget()
{
	return SNew(SOverlay);
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomRightWidget()
{
	return SNew(SOverlay);
}