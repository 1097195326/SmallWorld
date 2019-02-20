#include "BTTask_Arrive.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"


UBTTask_Arrive::UBTTask_Arrive():DecelerationTweaker(0.3f)
{

}
EBTNodeResult::Type UBTTask_Arrive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = SoldierController->SoldierPawn;
	
	FVector TargetLocation = SoldierController->CurrentLocation();
	FVector ToTarget = TargetLocation - SoldierPawn->GetActorLocation();
	if (TargetLocation.SizeSquared() > 0.f && ToTarget.SizeSquared() > 0.f)
	{
		float speed = ToTarget.Size() / DecelerationTweaker;
		speed = FMath::Min(speed, SoldierPawn->SoldierMovement->MaxSpeed);
		FVector DesiredVelocity = ToTarget.GetSafeNormal() * speed;
		
		SoldierController->AddSteeringForce(DesiredVelocity - SoldierPawn->GetVelocity());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}