#pragma once
#include "BaseBuildingActor.h"
#include "BakeryDataClass.h"

#include "BakeryActor.generated.h"

UCLASS()
class ABakeryActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ABakeryActor();

	virtual void On_Init() override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

};