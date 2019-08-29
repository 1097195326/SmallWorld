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
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
	void	AttackFunc();
	void	AttackPointFunc();
protected:
	class ASoldierPawn * SoldierPawn;
	bool		IsCallBack;
};