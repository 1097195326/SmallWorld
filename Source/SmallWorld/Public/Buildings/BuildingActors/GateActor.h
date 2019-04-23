#pragma once
#include "BaseBuildingActor.h"

#include "GateActor.generated.h"

UCLASS()
class AGateActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AGateActor();

	virtual void On_Init() override;

private:
	
};