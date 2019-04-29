#pragma once
#include "BaseBuildingActor.h"
#include "ArmyCenterData.h"

#include "ArmyCenterActor.generated.h"

UCLASS()
class AArmyCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AArmyCenterActor();

	virtual void On_Init() override;


};