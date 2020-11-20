#pragma once
#include "BaseBuildingActor.h"
#include "CommandCenterDataClass.h"
#include "SBaseCompoundWidget.h"

#include "CommandCenterActor.generated.h"

UCLASS()
class ACommandCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ACommandCenterActor();

	virtual void On_Init() override;

	virtual bool SetMeshComponentByIconName(const FString& InIconName) override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;
	virtual void RefreshView() override;

protected:
	TSharedPtr<SBaseCompoundWidget> ActorWidget;


};