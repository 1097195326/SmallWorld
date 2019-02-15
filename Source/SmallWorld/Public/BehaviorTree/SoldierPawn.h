#pragma once


#include "GamePawn.h"
#include "SoldierPawnMovement.h"
#include "BehaviorTree/BehaviorTree.h"
#include "SoldierPawn.generated.h"

UCLASS()
class ASoldierPawn : public AGamePawn
{
	GENERATED_BODY()
public:
	ASoldierPawn();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

public:
	UPROPERTY(EditAnywhere)
		UBehaviorTree * BehaviorTree;
	UPROPERTY(VisibleAnywhere)
		USoldierPawnMovement * SoldierMovement;

};