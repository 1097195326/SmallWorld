#include "SMiniMapWidget.h"
#include "SMiniMapViewport.h"
#include "GameStyle.h"


void SMiniMapWidget::Construct(const FArguments& InArgs)
{
	IsOpening = true;

	ChildSlot
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.AutoWidth()
			[
				SAssignNew(SwitchButton,SButton)
				//.ButtonStyle(&FXRStyle::Get().GetWidgetStyle<FButtonStyle>("MiniMapSwitchButtonOpen"))
				.OnClicked(this,&SMiniMapWidget::OnSwitchButtonClicked)
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.AutoWidth()
			[
				SAssignNew(ViewportContiner,SScaleBox)
				.Stretch(EStretch::ScaleToFill)
				[
					SNew(SBox)
					.WidthOverride(200)
					.HeightOverride(200)
					[
						SNew(SBorder)
						.BorderBackgroundColor(FLinearColor::Black)
						.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
						[
							SNew(SMiniMapViewport)
						]
					]
					
				]
			]
		];

}
FReply SMiniMapWidget::OnSwitchButtonClicked()
{
	IsOpening = !IsOpening;
	if (IsOpening)
	{
		//SwitchButton->SetButtonStyle(&FXRStyle::Get().GetWidgetStyle<FButtonStyle>("MiniMapSwitchButtonOpen"));
		ViewportContiner->SetVisibility(EVisibility::Visible);
	}
	else
	{
		//SwitchButton->SetButtonStyle(&FXRStyle::Get().GetWidgetStyle<FButtonStyle>("MiniMapSwitchButtonClose"));
		ViewportContiner->SetVisibility(EVisibility::Collapsed);
	}
	return FReply::Handled();
}