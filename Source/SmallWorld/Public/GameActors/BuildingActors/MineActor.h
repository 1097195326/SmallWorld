#pragma once
#include "BaseBuildingActor.h"

#include "MineActor.generated.h"

UCLASS()
class AMineActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AMineActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};