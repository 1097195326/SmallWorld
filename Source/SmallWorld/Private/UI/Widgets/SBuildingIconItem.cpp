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

	FString IconBrush = FString::Printf(TEXT("Icon.%s0"), *IconName);

	WoodDelegateHandle = DataManager::GetInstance()->WoodDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);
	StoneDelegateHandle = DataManager::GetInstance()->StoneDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);
	GoldDelegateHandle = DataManager::GetInstance()->GoldDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);


	const BuildingConfig & BConfig = DataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SBox)
				.WidthOverride(100)
				.HeightOverride(100)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[				
						SAssignNew(IconImage,SImage)
						.Image(FGameStyle::Get().GetBrush(*IconBrush))
					]
					+ SOverlay::Slot()
					[
						SAssignNew(IconButton,SButton)
						.ButtonColorAndOpacity(FGameStyle::Get().GetColor("Color.None"))
					]
				]
			]
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SAssignNew(IconText,STextBlock)
				.TextStyle(&FGameStyle::Get().GetWidgetStyle<FTextBlockStyle>("Text_12"))
				.Text(FText::FromString(BConfig.title))
			]
		];

	
	//RefreshView();
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
FReply SBuildingIconItem::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	return FReply::Handled();
}