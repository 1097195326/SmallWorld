#include "SBuildingIconItem.h"
#include "GameDataManager.h"
#include "FBuildingDragDropOp.h"
#include "GameStyle.h"


SBuildingIconItem::~SBuildingIconItem()
{
	
	GameDataManager::GetInstance()->StoneDataChangedDelegate.Remove(WoodDelegateHandle);
	GameDataManager::GetInstance()->StoneDataChangedDelegate.Remove(StoneDelegateHandle);
	GameDataManager::GetInstance()->WoodDataChangedDelegate.Remove(GoldDelegateHandle);
}
void SBuildingIconItem::Construct(const FArguments & InArgs)
{
	IconName = InArgs._IconName;

	FString IconBrush = FString::Printf(TEXT("Icon.%s0"), *IconName);
	
	FString IconTexturePath = FString::Printf(TEXT("/Game/UI/Texture/Icon%s0"), *IconName);
	UTexture2D * IconTexture = LoadObject<UTexture2D>(nullptr, *IconTexturePath, nullptr);
	Brush.SetResourceObject(IconTexture);

	WoodDelegateHandle = GameDataManager::GetInstance()->WoodDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);
	StoneDelegateHandle = GameDataManager::GetInstance()->StoneDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);
	GoldDelegateHandle = GameDataManager::GetInstance()->GoldDataChangedDelegate.AddSP(this, &SBuildingIconItem::OnDataChanged);


	const BuildingConfigStruct & BConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

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
						//.Image(&Brush)
					]
					/*+ SOverlay::Slot()
					[
						SAssignNew(IconButton,SButton)
						.ClickMethod(EButtonClickMethod::PreciseClick)
						.ButtonColorAndOpacity(FGameStyle::Get().GetColor("Color.None"))
					]*/
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

	HordeDataClass * UserHordeData = GameDataManager::GetInstance()->GetUserData()->GetHordeData();
	const BuildingConfigStruct & BConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

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
FReply SBuildingIconItem::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return FReply::Handled().DetectDrag(SharedThis(this),EKeys::LeftMouseButton);
	}
	return FReply::Unhandled();
}
FReply SBuildingIconItem::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	if (InTouchEvent.GetPointerIndex() == ETouchIndex::Touch1)
	{
		return FReply::Handled().DetectDrag(SharedThis(this), EKeys::LeftMouseButton);
	}
	return FReply::Unhandled();
}
FReply SBuildingIconItem::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	return FReply::Handled().BeginDragDrop(FBuildingDragDropOp::New(IconName));

}