#pragma once
#include "BaseBuildingActor.h"
#include "CommandCenterDataClass.h"
#include "SWrapCompoundWidget.h"

#include "CommandCenterActor.generated.h"

UCLASS()
class ACommandCenterActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ACommandCenterActor();

	virtual void On_Init() override;
	virtual void On_Tick(float DeltaSeconds);

	//virtual bool SetMeshComponentByIconName(const FString& InIconName) override;

	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;
	virtual void RefreshView() override;

protected:
	TSharedPtr<SWrapCompoundWidget> ActorWidget;


};