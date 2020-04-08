#pragma once
#include "BaseBuildingActor.h"
#include "FarmData.h"

#include "FarmActor.generated.h"

UCLASS()
class AFarmActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AFarmActor();

	virtual void On_Init() override;


};