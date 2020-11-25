#include "BTService_SoldierUpdate.h"
#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

UBTService_SoldierUpdate::UBTService_SoldierUpdate()
{
	preSoldierState = SoldierState::S_Idle;

}
void UBTService_SoldierUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LocationInGroup")), FVector(0,0,0));
	//UE_LOG(LogTemp, Log, TEXT("zhx -- service update"));

	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return;
	}
	FVector MoveLocation = SoldierPawn->GetMoveLocation();
	
	const FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("TargetLocation")));
	if (TargetLocation != MoveLocation)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("TargetLocation")), MoveLocation);
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("EnemyActor")), SoldierPawn->GetEnemy());
	

}