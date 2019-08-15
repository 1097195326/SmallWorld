#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackEnemy.generated.h"

UCLASS()
class UBTTask_AttackEnemy : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_AttackEnemy();

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
	void	AttackFunc();
	void	AttackPointFunc();
protected:
	class ASoldierPawn * SoldierPawn;
	bool		IsActive;
};