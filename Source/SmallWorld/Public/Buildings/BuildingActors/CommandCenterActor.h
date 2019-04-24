#pragma once
#include "BaseBuildingActor.h"

#include "CommandCenterActor.generated.h"

UCLASS()
class ACommandCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ACommandCenterActor();

	virtual void On_Init() override;


};