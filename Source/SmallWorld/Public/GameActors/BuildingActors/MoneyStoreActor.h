#pragma once
#include "BaseBuildingActor.h"
#include "MoneyStoreDataClass.h"

#include "MoneyStoreActor.generated.h"

UCLASS()
class AMoneyStoreActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AMoneyStoreActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};