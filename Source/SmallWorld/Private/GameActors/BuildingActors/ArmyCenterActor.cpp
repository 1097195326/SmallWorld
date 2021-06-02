#include "ArmyCenterActor.h"
#include "ArmyCenterDataClass.h"
#include "SGameActorDetail.h"
#include "SArmyCenterContent.h"
#include "SGameActorTitle.h"
#include "SGameActorOperation.h"
#include "GameDataManager.h"

AArmyCenterActor::AArmyCenterActor()
{
	

}
void AArmyCenterActor::On_Init()
{
	
}
TSharedPtr<SWidget>	AArmyCenterActor::CreateActorDetailWidget()
{
	SAssignNew(TitleWidget, SGameActorTitle)
		.ActorName(BuildingData->GetBuildingConfig().Title)
		.ActorLevel(FString::Printf(TEXT("%s%d"),*TransLanguage("Game_Level"), BuildingData->BuildingLevel))
		.ActorHealth(FString::Printf(TEXT("%s%.02f"), *TransLanguage("Game_Building_Level"), BuildingData->BuildingHealth));
	SAssignNew(ContentWidget, SArmyCenterContent)
		.ArmyCenter((ArmyCenterDataClass*)BuildingData);
	SAssignNew(OperationWidget, SGameActorOperation);

	return SNew(SGameActorDetail)
		.TitleWidget(TitleWidget)
		.ContentWidget(ContentWidget)
		.OperationWidget(OperationWidget)
		;
}
void AArmyCenterActor::RefreshView()
{
	if (ContentWidget.IsValid()) { ContentWidget->RefreshView(); }

}