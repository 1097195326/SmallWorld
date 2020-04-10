#include "SGameActorDetailWidget.h"



void SGameActorDetailWidget::Construct(const FArguments & InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Expose(TopSlot)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Expose(MiddleSlot)
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Expose(BottomSlot)
		];

}