#pragma once
#include "BaseBuildingActor.h"

#include "StoneActor.generated.h"

UCLASS()
class AStoneActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AStoneActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};