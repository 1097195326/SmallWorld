#pragma once
#include "BaseBuildingActor.h"
#include "FruitFarmData.h"

#include "FruitFarmActor.generated.h"

UCLASS()
class AFruitFarmActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AFruitFarmActor();

	virtual void On_Init() override;


};