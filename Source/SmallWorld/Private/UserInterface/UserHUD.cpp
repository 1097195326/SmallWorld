#include "UserHUD.h"
#include "UObject/ConstructorHelpers.h"

#include "UI/UIControllerManager.h"
#include "UI/MainViewUIController.h"
#include "UserPawn.h"
#include "UserController.h"


AUserHUD::AUserHUD()
{
	//ConstructorHelpers::FObjectFinder<UTexture2D> MainView(TEXT(""));

}
void AUserHUD::BeginPlay()
{
	Super::BeginPlay();

	UIControllerManager::GetInstance()->ChangeUIController(UIControllerManager::LoginViewUIControllerIndex);

}
void AUserHUD::DrawHUD()
{
	Super::DrawHUD();

}