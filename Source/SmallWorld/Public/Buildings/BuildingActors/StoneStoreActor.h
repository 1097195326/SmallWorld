#pragma once
#include "BaseBuildingActor.h"

#include "StoneStoreActor.generated.h"

UCLASS()
class AStoneStoreActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AStoneStoreActor();

	virtual void On_Init() override;


};