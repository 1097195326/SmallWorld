#include "ArmyCenterActor.h"
#include "ArmyCenterData.h"
#include "SGameActorDetailWidget.h"
#include "SArmyCenterOperationDetail.h"
#include "SGameActorDetailTitle.h"
#include "SBuildingDetailOperation.h"


AArmyCenterActor::AArmyCenterActor()
{
	

}
void AArmyCenterActor::On_Init()
{
	
}
TSharedPtr<SWidget>	AArmyCenterActor::CreateActorDetailWidget()
{
	TSharedPtr<SWidget> TitleWidget, DetailWidget, OperationWidget;

	SAssignNew(TitleWidget, SGameActorDetailTitle)
		.ActorName(BuildingData->GetConfigData().title)
		.ActorLevel(FString::Printf(TEXT("%s%d"),*TransLanguage("Game_Level"), BuildingData->BuildingLevel))
		.ActorHealth(FString::Printf(TEXT("%s%.02f"), *TransLanguage("Game_Building_Level"), BuildingData->BuildingHealth));
	SAssignNew(DetailWidget, SArmyCenterOperationDetail)
		.ArmyCenter((ArmyCenterData*)BuildingData);
	SAssignNew(OperationWidget, SBuildingDetailOperation);

	return SNew(SGameActorDetailWidget)
		.TitleWidget(TitleWidget)
		.DetailWidget(DetailWidget)
		.OperationWidget(OperationWidget)
		;
	return SNullWidget::NullWidget;
}