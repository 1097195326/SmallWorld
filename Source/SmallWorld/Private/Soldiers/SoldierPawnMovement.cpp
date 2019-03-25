#include "SoldierPawnMovement.h"
#include "SoldierPawn.h"
#include "SoldierPawnController.h"

void USoldierPawnMovement::BeginPlay()
{
	Super::BeginPlay();
	if (PawnOwner)
	{
		SoldierPawn = Cast<ASoldierPawn>(PawnOwner);
	}
}
void USoldierPawnMovement::ApplyControlInputToVelocity(float DeltaTime)
{
	//if (SoldierPawn->IsMove())
	{
		float PawnMass = SoldierPawn->fMass;

		FVector SteeringForce = SoldierPawn->SteeringForce();

		//FVector acceleration = SteeringForce / PawnMass;
		//Velocity += acceleration *DeltaTime;
		Velocity += SteeringForce;

		Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
		
		if (Velocity.SizeSquared() > 0.00000001f)
		{
			//SoldierPawn->SetActorLocationAndRotation( SoldierPawn->GetActorLocation() + Velocity * DeltaTime, Velocity.ToOrientationQuat(), true);
			SoldierPawn->SetActorRotation(Velocity.ToOrientationQuat());
		}
		
	}
}