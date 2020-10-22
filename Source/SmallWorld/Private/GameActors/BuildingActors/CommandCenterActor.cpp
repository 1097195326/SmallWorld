#include "CommandCenterActor.h"
#include "SGameActorTitle.h"
#include "SGameActorOperation.h"
#include "SGameActorDetail.h"
#include "GameDataManager.h"


ACommandCenterActor::ACommandCenterActor()
{
	

}
void ACommandCenterActor::On_Init()
{
	
}
TSharedPtr<SWidget>	ACommandCenterActor::CreateActorDetailWidget()
{
	SAssignNew(TitleWidget, SGameActorTitle)
		.ActorName(BuildingData->GetBuildingConfig().title)
		.ActorLevel(FString::Printf(TEXT("%s%d"), *TransLanguage("Game_Level"), BuildingData->BuildingLevel))
		.ActorHealth(FString::Printf(TEXT("%s%.02f"), *TransLanguage("Game_Building_Level"), BuildingData->BuildingHealth));
	/*SAssignNew(DetailWidget, SArmyCenterContent)
		.ArmyCenter((ArmyCenterDataClass*)BuildingData);*/
	SAssignNew(OperationWidget, SGameActorOperation);

	return SNew(SGameActorDetail)
		.TitleWidget(TitleWidget)
		//.ContentWidget(DetailWidget)
		.OperationWidget(OperationWidget)
		;
}
void ACommandCenterActor::RefreshView()
{
	DetailWidget.IsValid() ? DetailWidget->RefreshView() : NULL;

}