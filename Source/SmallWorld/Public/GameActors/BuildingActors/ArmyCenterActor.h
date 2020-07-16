#pragma once
#include "BaseBuildingActor.h"
#include "ArmyCenterDataClass.h"

#include "ArmyCenterActor.generated.h"

UCLASS()
class AArmyCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	AArmyCenterActor();

	// ------------- Override GameObjectClass ------------
	virtual void On_Init() override;
	// ----------- Override GameActor ----------
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;
	virtual void RefreshView() override;

protected:
	TSharedPtr<SBaseCompoundWidget> TitleWidget, DetailWidget, OperationWidget;

};