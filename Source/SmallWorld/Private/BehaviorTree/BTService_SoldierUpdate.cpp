#include "BTService_SoldierUpdate.h"
#include "SoldierPawnController.h"

#include "Engine.h"
#include "Kismet/GameplayStatics.h"

UBTService_SoldierUpdate::UBTService_SoldierUpdate()
{
	preSoldierState = S_Normal;

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
		case	S_Normal:
		{

		}break;
		case	S_Idle:
		{

		}break;
		case	S_FightSelf:
		{

		}break;
		case	S_FormationDefense:
		{

		}break;
		case	S_FormationFight:
		{

		}break;
		case	S_MoveToCity:
		{

		}break;
		case	S_MoveToGroup:
		{
			if (preSoldierState != SoldierState)
			{
				preSoldierState = SoldierState;
				OwnerComp.GetBlackboardComponent()->SetValue();

			}
		}break;
		case	S_ReadyInGroup:
		{

		}break;
		case	S_Dieing:
		{

		}break;
		case	S_Died:
		{

		}break;
		case	S_Hit:
		{

		}break;
		case	S_Victory:
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