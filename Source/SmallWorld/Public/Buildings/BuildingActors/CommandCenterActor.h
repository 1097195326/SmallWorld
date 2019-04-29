#pragma once
#include "BaseBuildingActor.h"
#include "CommandCenterData.h"

#include "CommandCenterActor.generated.h"

UCLASS()
class ACommandCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ACommandCenterActor();

	virtual void On_Init() override;


};