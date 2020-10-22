#include "SVGameActorIcon.h"
#include "GameDataManager.h"
#include "FBuildingDragDropOp.h"
#include "GameStyle.h"


SVGameActorIcon::~SVGameActorIcon()
{
	
	GameDataManager::GetInstance()->StoneDataChangedDelegate.Remove(WoodDelegateHandle);
	GameDataManager::GetInstance()->StoneDataChangedDelegate.Remove(StoneDelegateHandle);
	GameDataManager::GetInstance()->WoodDataChangedDelegate.Remove(GoldDelegateHandle);
}
void SVGameActorIcon::Construct(const FArguments & InArgs)
{
	IconName = InArgs._IconName;

	FString IconBrush = FString::Printf(TEXT("Icon.%s0"), *IconName);
	
	FString IconTexturePath = FString::Printf(TEXT("/Game/UI/Texture/Icon%s0"), *IconName);
	UTexture2D * IconTexture = LoadObject<UTexture2D>(nullptr, *IconTexturePath, nullptr);
	Brush.SetResourceObject(IconTexture);

	WoodDelegateHandle = GameDataManager::GetInstance()->WoodDataChangedDelegate.AddSP(this, &SVGameActorIcon::OnDataChanged);
	StoneDelegateHandle = GameDataManager::GetInstance()->StoneDataChangedDelegate.AddSP(this, &SVGameActorIcon::OnDataChanged);
	GoldDelegateHandle = GameDataManager::GetInstance()->GoldDataChangedDelegate.AddSP(this, &SVGameActorIcon::OnDataChanged);


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
void SVGameActorIcon::RefreshView()
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
void SVGameActorIcon::OnDataChanged()
{
	RefreshView();
}
FReply SVGameActorIcon::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return FReply::Handled().DetectDrag(SharedThis(this),EKeys::LeftMouseButton);
	}
	return FReply::Unhandled();
}
FReply SVGameActorIcon::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	if (InTouchEvent.GetPointerIndex() == ETouchIndex::Touch1)
	{
		return FReply::Handled().DetectDrag(SharedThis(this), EKeys::LeftMouseButton);
	}
	return FReply::Unhandled();
}
FReply SVGameActorIcon::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	return FReply::Handled().BeginDragDrop(FBuildingDragDropOp::New(IconName));

}