#pragma once
#include "BaseBuildingActor.h"
#include "FoodStoreDataClass.h"

#include "FoodStoreActor.generated.h"

UCLASS()
class AFoodStoreActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AFoodStoreActor();

	virtual void On_Init() override;
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;


};