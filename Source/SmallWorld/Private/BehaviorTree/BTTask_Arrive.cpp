#include "BTTask_Arrive.h"
#include "SoldierPawnController.h"
#include "SoldierPawn.h"


UBTTask_Arrive::UBTTask_Arrive():DecelerationTweaker(0.3f)
{

}
EBTNodeResult::Type UBTTask_Arrive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASoldierPawnController * SoldierController = Cast<ASoldierPawnController>(OwnerComp.GetAIOwner());
	

	return EBTNodeResult::Failed;
}