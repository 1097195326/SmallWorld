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
	vSteeringForce = FVector::ZeroVector;

	if (IsSeek())
	{
		vSteeringForce += Seek(vMoveToLocation);
	}
	if (IsArrive())
	{
		vSteeringForce += Arrive(vMoveToLocation);
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
	if (ToTarget.Size() > 0)
	{
		FVector vv = SoldierPawn->GetVelocity();
		float speed = ToTarget.Size() / (SoldierPawn->SoldierMovement->Deceleration * 0.3f);
		speed = FMath::Min(speed, SoldierPawn->SoldierMovement->MaxSpeed);
		FVector DesiredVelocity = ToTarget.GetSafeNormal() * speed;

		return DesiredVelocity - vv;
	}
	return FVector::ZeroVector;
}
FVector ASoldierPawnController::OffsetPursuit(ASoldierPawn * Leader)
{
	FVector ToOffset = SoldierPawn->mOffsetToLeader - SoldierPawn->GetActorLocation();

	float LookAheadTime = ToOffset.Size() / (SoldierPawn->SoldierMovement->MaxSpeed + Leader->GetVelocity().Size());

	return Arrive(SoldierPawn->mOffsetToLeader + Leader->GetVelocity() * LookAheadTime);
}
FVector ASoldierPawnController::Separation( BaseGroup * Group)
{
	FVector Steer = FVector::ZeroVector;
	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
	for (;iter != Soldiers.end();iter++)
	{
		ASoldierPawn * soldier = *iter;
		if (soldier != SoldierPawn)
		{
			FVector ToTarget = SoldierPawn->GetActorLocation() - soldier->GetActorLocation();
			Steer += ToTarget.GetSafeNormal() / ToTarget.Size();
		}
	}
	return Steer;
}
FVector ASoldierPawnController::Alignment( BaseGroup * Group)
{
	FVector AverageHeading = FVector::ZeroVector;
	int    NeighborCount = 0;

	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
	for (; iter != Soldiers.end(); iter++)
	{
		ASoldierPawn * soldier = *iter;
		if (soldier != SoldierPawn)
		{
			AverageHeading += soldier->GetActorForwardVector();
			++NeighborCount;
		}
	}
	if (NeighborCount > 0)
	{
		AverageHeading /= NeighborCount;
		AverageHeading -= SoldierPawn->GetActorForwardVector();
	}
	return AverageHeading;
}
FVector ASoldierPawnController::Cohesion( BaseGroup *  Group)
{
	FVector CenterOfMass, Steering;

	int NeighborCount = 0;

	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
	for (; iter != Soldiers.end(); iter++)
	{
		ASoldierPawn * soldier = *iter;
		CenterOfMass += soldier->GetActorLocation();
		++NeighborCount;
	}
	if (NeighborCount > 0)
	{
		CenterOfMass /= NeighborCount;
		Steering = Seek(CenterOfMass);
	}
	return Steering;
}