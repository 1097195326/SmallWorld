#pragma once
#include "BaseBuildingActor.h"
#include "GateData.h"

#include "GateActor.generated.h"

UCLASS()
class AGateActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AGateActor();

	virtual void On_Init() override;
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

private:
	
};