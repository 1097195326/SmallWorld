#include "CommandCenterActor.h"
#include "SCommandCenter.h"
#include "GameDataManager.h"


ACommandCenterActor::ACommandCenterActor()
{
	

}
void ACommandCenterActor::On_Init()
{
	
}
TSharedPtr<SWidget>	ACommandCenterActor::CreateActorDetailWidget()
{
	SAssignNew(ActorWidget, SCommandCenter)
		.CommandCenterData((CommandCenterDataClass*)BuildingData);

	return ActorWidget;
}
void ACommandCenterActor::RefreshView()
{
	ActorWidget.IsValid() ? ActorWidget->RefreshView() : NULL;

}