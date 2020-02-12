#include "SShowBuildingWidget.h"
#include "DataManager.h"
#include "SBuildingIconItem.h"


void SShowBuildingWidget::Construct(const FArguments & InArgs)
{
	IconNames = InArgs._IconNames;

	ChildSlot
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SAssignNew(IconGridPanel, SGridPanel)
			]
		];

	HordeData * UserHordeData = DataManager::GetInstance()->GetUserData()->GetHordeData();
	
	int temIndex = 0;
	for (auto IconName : IconNames)
	{
		const BuildingConfig & BConfig = DataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

		int32 IconRow = temIndex / 8;
		int32 IconColumn = temIndex % 8;
		IconGridPanel->AddSlot(IconColumn,IconRow)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Center)
		.Padding(5)
				[
					SNew(SBuildingIconItem)
					.IconName(IconName)
				];
		++temIndex;
	}

}

/*
void SShowBuildingWidget::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

}
void SShowBuildingWidget::OnDragLeave(const FDragDropEvent& DragDropEvent)
{

}
FReply SShowBuildingWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

	return FReply::Handled();
}
FReply SShowBuildingWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

	return FReply::Handled();
}*/