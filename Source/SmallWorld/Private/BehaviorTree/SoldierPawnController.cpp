#include "SoldierPawnController.h"

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
	if (IsSeek())
	{
		vSteeringForce += Seek(vMoveToLocation);
	}
	if (IsArrive())
	{
		vSteeringForce = Arrive(vMoveToLocation);
	}
	return vSteeringForce.GetClampedToMaxSize(SoldierPawn->fMaxForce);
}
void ASoldierPawnController::SetMoveToLocation(FVector Location)
{
	vMoveToLocation = Location;
}
FVector ASoldierPawnController::MoveToLocation()
{
	return vMoveToLocation;
}
// ----------------------  behavior tree -------------------

FVector ASoldierPawnController::Seek(FVector TargetLocation)
{
	FVector DesiredVelocity = (TargetLocation - SoldierPawn->GetActorLocation()).GetSafeNormal() * SoldierPawn->SoldierMovement->MaxSpeed;

	return DesiredVelocity - SoldierPawn->GetVelocity();
}
FVector ASoldierPawnController::Arrive(FVector TargetLocation)
{
	FVector ToTarget = TargetLocation - SoldierPawn->GetActorLocation();
	
	/*static bool isArrive = false;
	
	if (!isArrive && ToTarget.Size() < 0.1f)
	{
		isArrive = true;
	}
	if (isArrive)
	{
		vSteeringForce = FVector::ZeroVector;
		return vSteeringForce;
	}*/
	float speed = ToTarget.Size() / (SoldierPawn->SoldierMovement->Deceleration);
	speed = FMath::Min(speed, SoldierPawn->SoldierMovement->MaxSpeed);
	FVector DesiredVelocity = ToTarget.GetSafeNormal() * speed;
	
	FVector VV = SoldierPawn->GetVelocity();
	return DesiredVelocity - VV;
}
FVector ASoldierPawnController::OffsetPursuit(ASoldierPawn * Leader)
{
	FVector ToOffset = SoldierPawn->mOffsetToLeader - SoldierPawn->GetActorLocation();

	float LookAheadTime = ToOffset.Size() / (SoldierPawn->SoldierMovement->MaxSpeed + Leader->GetVelocity().Size());

	return Arrive(SoldierPawn->mOffsetToLeader + Leader->GetVelocity() * LookAheadTime);
}