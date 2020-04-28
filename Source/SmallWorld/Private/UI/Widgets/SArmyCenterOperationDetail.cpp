#include "SArmyCenterOperationDetail.h"
#include "DataManager.h"
#include "SHorizontalIconTextItem.h"
#include "SHorizontalItemOperation.h"
#include "ArmyCenterData.h"


void SArmyCenterOperationDetail::Construct(const FArguments & InArgs)
{
	ArmyCenter = InArgs._ArmyCenter;

	TSharedPtr<SVerticalBox> ItemList;
	ChildSlot.Padding(24,0,0,0)
		[
			SAssignNew(ItemList, SVerticalBox)
		];

	
	ItemList->AddSlot()
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
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
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				[
					SNew(SHorizontalIconTextItem)
					.InImageBrush(FGameStyle::Get().GetBrush(*IconBrush))
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				[
					SNew(SHorizontalItemOperation)
				]
			];
	}


}