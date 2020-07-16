#pragma once
#include "BaseBuildingActor.h"
#include "WoodStoneStoreDataClass.h"

#include "WoodStoneStoreActor.generated.h"

UCLASS()
class AWoodStoneStoreActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AWoodStoneStoreActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};