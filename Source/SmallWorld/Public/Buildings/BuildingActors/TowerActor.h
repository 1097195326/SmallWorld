#pragma once
#include "BaseBuildingActor.h"

#include "TowerActor.generated.h"

UCLASS()
class ATowerActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ATowerActor();

	virtual void On_Init() override;
	

};