#include "BTTask_Seek.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
//
//UBTTask_Seek::UBTTask_Seek(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//
//}
EBTNodeResult::Type UBTTask_Seek::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	if (SoldierController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	ASoldierPawn * SoldierPawn = SoldierController->SoldierPawn;
	if (SoldierPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	FVector TargetLocation = SoldierController->CurrentLocation();
	if ((TargetLocation - SoldierPawn->GetActorLocation()).SizeSquared() > SoldierPawn->fFieldOfView * SoldierPawn->fFieldOfView)
	{
		return EBTNodeResult::Failed;
	}
	FVector DesiredVelocity = (TargetLocation - SoldierPawn->GetActorLocation()).GetSafeNormal() * SoldierPawn->SoldierMovement->MaxSpeed;
	
	SoldierController->AddSteeringForce(DesiredVelocity - SoldierPawn->GetVelocity());

	return EBTNodeResult::Succeeded;
}