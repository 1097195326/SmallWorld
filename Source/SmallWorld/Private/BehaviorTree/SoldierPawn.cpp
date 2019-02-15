#include "SoldierPawn.h"
#include "SoldierPawnController.h"


ASoldierPawn::ASoldierPawn()
{

	AIControllerClass = ASoldierPawnController::StaticClass();

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SoldierMovement = CreateDefaultSubobject<USoldierPawnMovement>(TEXT("SoldierMovement"));
	SoldierMovement->SetUpdatedComponent(RootComponent);
	

}
void ASoldierPawn::On_Init()
{

}
void ASoldierPawn::On_Start()
{

}
void ASoldierPawn::On_Tick(float delta)
{

}
void ASoldierPawn::On_Delete()
{

}