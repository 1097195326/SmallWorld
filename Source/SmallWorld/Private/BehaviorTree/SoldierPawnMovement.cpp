#include "SoldierPawnMovement.h"
#include "SoldierPawn.h"
#include "SoldierPawnController.h"

void USoldierPawnMovement::BeginPlay()
{
	Super::BeginPlay();
	if (PawnOwner)
	{
		SoldierPawn = Cast<ASoldierPawn>(PawnOwner);
		SoldierController = Cast<ASoldierPawnController>(PawnOwner->GetController());
	}
}
void USoldierPawnMovement::ApplyControlInputToVelocity(float DeltaTime)
{
	//if (SoldierPawn->IsMove())
	{
		float PawnMass = SoldierPawn->fMass;

		FVector SteeringForce = SoldierController->SteeringForce();

		FVector acceleration = SteeringForce / PawnMass;

		Velocity += acceleration * DeltaTime;

		Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);

		SoldierPawn->SetActorRotation(Velocity.ToOrientationQuat());
	}
}