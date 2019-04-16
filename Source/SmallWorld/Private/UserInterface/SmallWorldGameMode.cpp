#include "SmallWorldGameMode.h"
#include "UserController.h"
#include "UserHUD.h"
#include "UserPawn.h"
#include "GameWorld.h"


ASmallWorldGameMode::ASmallWorldGameMode()
{
	PlayerControllerClass = AUserController::StaticClass();
	//DefaultPawnClass = AUserPawn::StaticClass();
	//DefaultPawnClass = ADefaultPawn::StaticClass();
	HUDClass = AUserHUD::StaticClass();

}
void ASmallWorldGameMode::StartPlay()
{
	Super::StartPlay();

	GameWorld::GetInstance()->BuildWorld();

}