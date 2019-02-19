#include "BTService_SoldierUpdate.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

void UBTService_SoldierUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	if (SoldierController == nullptr)
	{
		return;
	}
	ASoldierPawn * SoldierPawn = SoldierController->SoldierPawn;
	if (SoldierPawn)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("zhx -- service update"));

	static bool IsSet = false;
	if (!IsSet)
	{
		IsSet = true;
		TArray<AActor*> Points;
		UGameplayStatics::GetAllActorsOfClass(SoldierPawn->GetWorld(), ATargetPoint::StaticClass(), Points);

		for (int i = 0 ;i < Points.Num(); i++)
		{
			ATargetPoint * Point = Cast<ATargetPoint>(Points[i]);
			SoldierController->SetCurrentLocation(Point->GetActorLocation());
		}

	}

}