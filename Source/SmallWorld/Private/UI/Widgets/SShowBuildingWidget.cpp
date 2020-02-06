#include "SShowBuildingWidget.h"
#include "DataManager.h"
#include "SBuildingIconItem.h"


void SShowBuildingWidget::Construct(const FArguments & InArgs)
{
	IconNames = InArgs._IconNames;

	ChildSlot
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(IconGridPanel,SGridPanel)
			]
		];

	HordeData * UserHordeData = DataManager::GetInstance()->GetUserData()->GetHordeData();
	
	int temIndex = 0;
	for (auto IconName : IconNames)
	{
		const BuildingConfig & BConfig = DataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(IconName);

		int32 IconRow = temIndex / 5;
		int32 IconColumn = temIndex % 5;
		IconGridPanel->AddSlot(IconColumn,IconRow)
				[
					SNew(SBuildingIconItem)
					.IconName(IconName)
				];
		++temIndex;
	}

}