#include "SoldierPawnMovement.h"
#include "SoldierPawn.h"
#include "SoldierPawnController.h"

void USoldierPawnMovement::InitializeComponent()
{
	Super::InitializeComponent();
	if (PawnOwner)
	{
		SoldierPawn = Cast<ASoldierPawn>(PawnOwner);
		SoldierController = Cast<ASoldierPawnController>(PawnOwner->GetController());
	}
}
void USoldierPawnMovement::ApplyControlInputToVelocity(float DeltaTime)
{
	if (SoldierController == nullptr)
	{
		if (SoldierPawn->GetController())
		{
			SoldierController = Cast<ASoldierPawnController>(PawnOwner->GetController());
		}
		return;
	}
	float PawnMass = SoldierPawn->fMass;
	if (SoldierController)
	{
		FVector SteeringForce = SoldierController->SteeringForce();

		FVector acceleration = SteeringForce / PawnMass;

		Velocity += acceleration * DeltaTime;

		Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
	}
	

}