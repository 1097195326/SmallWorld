#pragma once
#include "BaseBuildingActor.h"
#include "WallDataClass.h"

#include "WallActor.generated.h"

UCLASS()
class AWallActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AWallActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};