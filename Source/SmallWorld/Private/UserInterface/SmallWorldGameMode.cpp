#include "SmallWorldGameMode.h"
#include "UserController.h"
#include "UserHUD.h"
#include "UserPawn.h"
#include "GameManager.h"


ASmallWorldGameMode::ASmallWorldGameMode()
{
	PlayerControllerClass = AUserController::StaticClass();
	DefaultPawnClass = AUserPawn::StaticClass();
	//DefaultPawnClass = ADefaultPawn::StaticClass();
	HUDClass = AUserHUD::StaticClass();

}
void ASmallWorldGameMode::StartPlay()
{
	Super::StartPlay();

	UE_LOG(LogTemp, Log, TEXT("zhx:ASmallWorldGameMode::StartPlay"));

	//GameManager::GetInstance()->ScanWorldMap();

}