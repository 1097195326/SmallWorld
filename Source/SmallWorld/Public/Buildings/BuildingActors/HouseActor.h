#pragma once
#include "BaseBuildingActor.h"

#include "HouseActor.generated.h"

UCLASS()
class AHouseActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AHouseActor();

	virtual void On_Init() override;


};