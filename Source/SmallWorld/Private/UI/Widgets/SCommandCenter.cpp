#include "SCommandCenter.h"
#include "GameDataManager.h"
#include "SHGameActorIcon.h"
#include "CommandCenterDataClass.h"
#include "GameStyle.h"


void SCommandCenter::Construct(const FArguments & InArgs)
{
	CommandCenterData = InArgs._CommandCenterData;

	TSharedPtr<SVerticalBox> ItemList;
	ChildSlot.Padding(24, 0, 0, 0)
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		[
			SAssignNew(ItemList, SVerticalBox)
		];
	ItemList->AddSlot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.AutoHeight()
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Move"))
			.OnClicked(this, &SCommandCenter::OnButtonClicked,1)
		];
}
void SCommandCenter::RefreshView()
{


}
FReply SCommandCenter::OnButtonClicked(int32 InIndex)
{
	switch (InIndex)
	{
	case 1:
	{
		CommandCenterData->BuildingActor->GetCastleTileActor();
		break;
	}
	}
	return FReply::Handled();
}