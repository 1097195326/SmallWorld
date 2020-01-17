#include "SBuildingIconItem.h"
#include "DataManager.h"



SBuildingIconItem::~SBuildingIconItem()
{
	
	DataManager::GetInstance()->StoneDataChangedDelegate.Remove(WoodDelegateHandle);
	DataManager::GetInstance()->StoneDataChangedDelegate.Remove(StoneDelegateHandle);
	DataManager::GetInstance()->WoodDataChangedDelegate.Remove(GoldDelegateHandle);
}
void SBuildingIconItem::Construct(const FArguments & InArgs)
{
	IconName = InArgs._IconName;

	const BuildingConfig & BConfig = DataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(SBox)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[				
						SAssignNew(IconImage,SImage)	
					]
					+ SOverlay::Slot()
					[
						SAssignNew(IconButton,SButton)
					]
				]
			]
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SAssignNew(IconText,STextBlock)
				.TextStyle(&FGameStyle::Get().GetWidgetStyle<FTextBlockStyle>("Text_12"))
				.Text(BConfig.title)
			]
		];

	WoodDelegateHandle = DataManager::GetInstance()->WoodDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);
	StoneDelegateHandle = DataManager::GetInstance()->StoneDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);
	GoldDelegateHandle = DataManager::GetInstance()->GoldDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);

}
void SBuildingIconItem::RefreshView()
{
	int32 GoldNum, WoodNum, StoneNum;

	HordeData * UserHordeData = DataManager::GetInstance()->GetUserData()->GetHordeData();
	const BuildingConfig & BConfig = DataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

	GoldNum = UserHordeData->GetGoldNum();
	WoodNum = UserHordeData->GetWoodNum();
	StoneNum = UserHordeData->GetStoneNum();

	if (GoldNum >= BConfig.LevelInfos[0].upmoney &&
		WoodNum >= BConfig.LevelInfos[0].upwood  &&
		StoneNum >= BConfig.LevelInfos[0].upstone)
	{

	}
	else
	{

	}
}
void SBuildingIconItem::OnDataChanged()
{
	RefreshView();
}