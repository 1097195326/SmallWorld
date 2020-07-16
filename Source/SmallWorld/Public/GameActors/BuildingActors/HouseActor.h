#pragma once
#include "BaseBuildingActor.h"
#include "HouseDataClass.h"

#include "HouseActor.generated.h"

UCLASS()
class AHouseActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AHouseActor();

	virtual void On_Init() override;
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;


};