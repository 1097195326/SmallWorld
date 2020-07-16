#pragma once
#include "BaseBuildingActor.h"
#include "FruitFarmDataClass.h"

#include "FruitFarmActor.generated.h"

UCLASS()
class AFruitFarmActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AFruitFarmActor();

	virtual void On_Init() override;
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;


};