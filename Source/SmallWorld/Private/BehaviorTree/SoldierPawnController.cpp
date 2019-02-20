#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ASoldierPawnController::ASoldierPawnController(const FObjectInitializer& ObjectInitializer /* = FObjectInitializer::Get() */)
{
	

}
void ASoldierPawnController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	SoldierPawn = Cast<ASoldierPawn>(InPawn);

	// start behavior
	if (SoldierPawn && SoldierPawn->BehaviorTree)
	{
		RunBehaviorTree(SoldierPawn->BehaviorTree);
	}

}
void ASoldierPawnController::UnPossess()
{
	Super::UnPossess();

	Cast<UBehaviorTreeComponent>(BrainComponent)->StopTree();

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