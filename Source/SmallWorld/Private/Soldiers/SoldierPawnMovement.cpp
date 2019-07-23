#include "SoldierPawnMovement.h"
#include "SoldierPawn.h"
#include "SoldierPawnController.h"



USoldierPawnMovement::USoldierPawnMovement()
{

}
USoldierPawnMovement::~USoldierPawnMovement()
{

}
void USoldierPawnMovement::BeginPlay()
{
	Super::BeginPlay();
	if (PawnOwner)
	{
		SoldierPawn = Cast<ASoldierPawn>(PawnOwner);
	}
}
//void USoldierPawnMovement::ApplyControlInputToVelocity(float DeltaTime)
//{
//	//if (SoldierPawn->IsMove())
//	{
//		//float PawnMass = SoldierPawn->fMass;
//
//		//FVector SteeringForce = SoldierPawn->SteeringForce();
//
//		////FVector acceleration = SteeringForce / PawnMass;
//		////Velocity += acceleration *DeltaTime;
//		//Velocity += SteeringForce;
//
//		//Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
//		//
//		//if (Velocity.SizeSquared() > 0.00000001f)
//		//{
//		//	//SoldierPawn->SetActorLocationAndRotation( SoldierPawn->GetActorLocation() + Velocity * DeltaTime, Velocity.ToOrientationQuat(), true);
//		//	SoldierPawn->SetActorRotation(Velocity.ToOrientationQuat());
//		//}
//		
//	}
//}

//
//void USoldierPawnMovement::AddSteeringForce(FVector Force)
//{
//	vSteeringForce += Force;
//}
//FVector USoldierPawnMovement::SteeringForce()
//{
//	vSteeringForce = FVector::ZeroVector;
//
//	if (SoldierPawn->IsSeek())
//	{
//		vSteeringForce += Seek(SoldierPawn->vMoveToLocation);
//	}
//	if (SoldierPawn->IsArrive())
//	{
//		vSteeringForce += Arrive(vMoveToLocation);
//	}
//	return vSteeringForce.GetClampedToMaxSize(fMaxForce);
//}
//// ----------------------  behavior tree -------------------
//
//FVector USoldierPawnMovement::Seek(FVector TargetLocation)
//{
//	FVector DesiredVelocity = (TargetLocation - GetActorLocation()).GetSafeNormal() * SoldierMovement->MaxSpeed;
//
//	return DesiredVelocity - GetVelocity();
//}
//FVector USoldierPawnMovement::Arrive(FVector TargetLocation)
//{
//	FVector ToTarget = TargetLocation - GetActorLocation();
//	if (ToTarget.Size() > 0)
//	{
//		FVector vv = GetVelocity();
//		float speed = ToTarget.Size() / (SoldierMovement->Deceleration * 0.3f);
//		speed = FMath::Min(speed, SoldierMovement->MaxSpeed);
//		FVector DesiredVelocity = ToTarget.GetSafeNormal() * speed;
//
//		return DesiredVelocity - vv;
//	}
//	return FVector::ZeroVector;
//}
//FVector USoldierPawnMovement::OffsetPursuit(ASoldierPawn * Leader)
//{
//	FVector ToOffset = mOffsetToLeader - GetActorLocation();
//
//	float LookAheadTime = ToOffset.Size() / (SoldierMovement->MaxSpeed + Leader->GetVelocity().Size());
//
//	return Arrive(mOffsetToLeader + Leader->GetVelocity() * LookAheadTime);
//}
//FVector USoldierPawnMovement::Separation(SoldierGroup * Group)
//{
//	FVector Steer = FVector::ZeroVector;
//	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
//	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
//	for (; iter != Soldiers.end(); iter++)
//	{
//		ASoldierPawn * soldier = *iter;
//		if (soldier != this)
//		{
//			FVector ToTarget = GetActorLocation() - soldier->GetActorLocation();
//			Steer += ToTarget.GetSafeNormal() / ToTarget.Size();
//		}
//	}
//	return Steer;
//}
//FVector USoldierPawnMovement::Alignment(SoldierGroup * Group)
//{
//	FVector AverageHeading = FVector::ZeroVector;
//	int    NeighborCount = 0;
//
//	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
//	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
//	for (; iter != Soldiers.end(); iter++)
//	{
//		ASoldierPawn * soldier = *iter;
//		if (soldier != this)
//		{
//			AverageHeading += soldier->GetActorForwardVector();
//			++NeighborCount;
//		}
//	}
//	if (NeighborCount > 0)
//	{
//		AverageHeading /= NeighborCount;
//		AverageHeading -= GetActorForwardVector();
//	}
//	return AverageHeading;
//}
//FVector USoldierPawnMovement::Cohesion(SoldierGroup *  Group)
//{
//	FVector CenterOfMass, Steering;
//
//	int NeighborCount = 0;
//
//	list<ASoldierPawn*> Soldiers = Group->GetAllSoldier();
//	list<ASoldierPawn*>::iterator iter = Soldiers.begin();
//	for (; iter != Soldiers.end(); iter++)
//	{
//		ASoldierPawn * soldier = *iter;
//		CenterOfMass += soldier->GetActorLocation();
//		++NeighborCount;
//	}
//	if (NeighborCount > 0)
//	{
//		CenterOfMass /= NeighborCount;
//		Steering = Seek(CenterOfMass);
//	}
//	return Steering;
//}