#include "SArmyCenterOperationDetail.h"
#include "DataManager.h"
#include "SHorizontalIconTextItem.h"
#include "SHorizontalItemOperation.h"
#include "ArmyCenterData.h"
#include "GameStyle.h"


void SArmyCenterOperationDetail::Construct(const FArguments & InArgs)
{
	ArmyCenter = InArgs._ArmyCenter;

	TSharedPtr<SVerticalBox> ItemList;
	ChildSlot.Padding(24,0,0,0)
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
		SNew(SHorizontalIconTextItem)
		.InImageBrush( FGameStyle::Get().GetBrush("Icon.Peasant"))

	];
	for(auto soldierName : GameConfigData::SoldierNames)
	{
		FString IconBrush = FString::Printf(TEXT("Icon.%s"),*soldierName);
		ItemList->AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(SHorizontalIconTextItem)
					.InImageBrush(FGameStyle::Get().GetBrush(*IconBrush))
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(SHorizontalItemOperation)
				]
			];
	}


}