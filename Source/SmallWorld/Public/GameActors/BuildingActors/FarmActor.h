#pragma once
#include "BaseBuildingActor.h"
#include "FarmDataClass.h"

#include "FarmActor.generated.h"

UCLASS()
class AFarmActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AFarmActor();

	virtual void On_Init() override;
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;


};