#include "SBuildingIconList.h"
#include "GameDataManager.h"
#include "SVGameActorIcon.h"
#include "GameStyle.h"


void SBuildingIconList::Construct(const FArguments & InArgs)
{
	IconNames = InArgs._IconNames;

	ChildSlot
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SScaleBox)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.7F6E6F70"))
				.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Center)
					.Padding(5)
					.AutoHeight()
					[
						SAssignNew(IconGridPanel, SGridPanel)
					]
				]
			]
			
		];

	HordeDataClass * UserHordeData = GameDataManager::GetInstance()->GetUserData()->GetHordeData();
	
	int temIndex = 0;
	for (auto IconName : IconNames)
	{
		const BuildingConfigStruct & BConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

		int32 IconRow = temIndex / 8;
		int32 IconColumn = temIndex % 8;
		IconGridPanel->AddSlot(IconColumn,IconRow)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Center)
		.Padding(5)
				[
					SNew(SVGameActorIcon)
					.IconName(IconName)
				];
		++temIndex;
	}

}


void SBuildingIconList::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

}
void SBuildingIconList::OnDragLeave(const FDragDropEvent& DragDropEvent)
{

}
FReply SBuildingIconList::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

	return FReply::Handled();
}
FReply SBuildingIconList::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

	return FReply::Handled();
}