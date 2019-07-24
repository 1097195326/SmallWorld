#pragma once
#include "GameFramework/FloatingPawnMovement.h"

#include "SoldierPawnMovement.generated.h"

UCLASS()
class USoldierPawnMovement :public UFloatingPawnMovement
{
	GENERATED_BODY()
public:
	/*USoldierPawnMovement();
		~USoldierPawnMovement();*/
	virtual void BeginPlay() override;
	//virtual void ApplyControlInputToVelocity(float DeltaTime) override;

protected:
	/*void			AddSteeringForce(FVector Force);
	FVector			SteeringForce();

	FVector					Seek(FVector TargetLocation);
	FVector					Arrive(FVector TargetLocation);
	FVector					OffsetPursuit(ASoldierPawn * Leader);
	FVector					Separation(SoldierGroup *  Group);
	FVector					Alignment(SoldierGroup *  Group);
	FVector					Cohesion(SoldierGroup *  Group);*/

private:
	FVector					vSteeringForce;

	class ASoldierPawn * SoldierPawn;
	class ASoldierPawnController * SoldierController;

};