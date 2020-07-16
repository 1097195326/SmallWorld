#pragma once
#include "BaseBuildingActor.h"
#include "MillDataClass.h"

#include "MillActor.generated.h"

UCLASS()
class AMillActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AMillActor();

	virtual void On_Init() override;
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

private:



};