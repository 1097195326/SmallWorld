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

	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LocationInGroup")), FVector(0,0,0));
	//UE_LOG(LogTemp, Log, TEXT("zhx -- service update"));


	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	ASoldierPawn * SoldierPawn = Cast<ASoldierPawn>(SoldierController->GetPawn());
	if (SoldierController == nullptr || SoldierPawn == nullptr)
	{
		return;
	}

	
	SoldierState soldierState = SoldierPawn->GetSoldierState();

	switch (soldierState)
	{
		case	SoldierState::S_Normal:
		{

		}break;
		case	SoldierState::S_Idle:
		{
			
			SoldierPawn->SetSoldierAnimState(Anim_Idle);
			
		}break;
		case	SoldierState::S_FightSelf:
		{
			if (SoldierPawn->IsHaveEnemy())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LocationInGroup")), SoldierPawn->GetEnemy()->GetActorLocation());
			}
			else
			{

			}
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
			
				const FVector location = SoldierPawn->GetLocationInGroup();
				const FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("LocationInGroup")));
				if (targetLocation != location /*|| preSoldierState != SoldierState::S_MoveToGroup*/)
				{
					SoldierPawn->SetSoldierAnimState(Anim_Walk);
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LocationInGroup")), location);
				}
				else
				{
					//preSoldierState = SoldierState::S_MoveToGroup;
					
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