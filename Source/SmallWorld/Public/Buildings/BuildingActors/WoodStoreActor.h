#pragma once
#include "BaseBuildingActor.h"

#include "WoodStoreActor.generated.h"

UCLASS()
class AWoodStoreActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AWoodStoreActor();

	virtual void On_Init() override;


};
