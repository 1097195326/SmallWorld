#include "BTService_SoldierUpdate.h"
#include "SoldierPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

UBTService_SoldierUpdate::UBTService_SoldierUpdate()
{
	preSoldierState = SoldierState::S_Normal;

}
void UBTService_SoldierUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("zhx -- service update"));

	SoldierState SoldierState = SoldierPawn->GetSoldierState();

	switch (SoldierState)
	{
		case	SoldierState::S_Normal:
		{

		}break;
		case	SoldierState::S_Idle:
		{

		}break;
		case	SoldierState::S_FightSelf:
		{

		}break;
		case	SoldierState::S_FormationDefense:
		{

		}break;
		case	SoldierState::S_FormationFight:
		{

		}break;
		case	SoldierState::S_MoveToCity:
		{

		}break;
		case	SoldierState::S_MoveToGroup:
		{
			if (preSoldierState != SoldierState)
			{
				preSoldierState = SoldierState;

				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LocationInGroup")),SoldierPawn->GetLocationInGroup());

			}
		}break;
		case	SoldierState::S_ReadyInGroup:
		{

		}break;
		case	SoldierState::S_Dieing:
		{

		}break;
		case	SoldierState::S_Died:
		{

		}break;
		case	SoldierState::S_Hit:
		{

		}break;
		case	SoldierState::S_Victory:
		{

		}break;
	}

	/*if (SoldierController->MoveToLocation() == FVector::ZeroVector)
	{
		TArray<AActor*> Points;
		UGameplayStatics::GetAllActorsOfClass(SoldierPawn->GetWorld(), ATargetPoint::StaticClass(), Points);

		for (int i = 0 ;i < Points.Num(); i++)
		{
			ATargetPoint * Point = Cast<ATargetPoint>(Points[i]);
			SoldierController->SetMoveToLocation(Point->GetActorLocation());
		}

	}*/

}