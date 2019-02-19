#include "SoldierPawnController.h"
#include "SoldierPawn.h"



void ASoldierPawnController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	SoldierPawn = Cast<ASoldierPawn>(InPawn);

	if (SoldierPawn && SoldierPawn->BehaviorTree)
	{
		RunBehaviorTree(SoldierPawn->BehaviorTree);

	}
}
void ASoldierPawnController::UnPossess()
{
	Super::UnPossess();

}
void ASoldierPawnController::AddSteeringForce(FVector Force)
{
	vSteeringForce += Force;
}
FVector ASoldierPawnController::SteeringForce()
{
	return vSteeringForce.GetClampedToMaxSize(SoldierPawn->fMaxForce);
}
void ASoldierPawnController::SetCurrentLocation(FVector Location)
{
	vCurrentLocation = Location;
}
FVector ASoldierPawnController::CurrentLocation()
{
	return vCurrentLocation;
}