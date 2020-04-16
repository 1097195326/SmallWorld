#include "SMiniMapWidget.h"
#include "GameStyle.h"

#include "PreviewActor.h"


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
					.WidthOverride(800)
					.HeightOverride(800)
					[
						SNew(SBorder)
						.BorderBackgroundColor(FLinearColor::Black)
						.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
						[
							SAssignNew(PreviewViewport,SMiniMapViewport)
						]
					]
					
				]
			]
		];
	PreviewViewport->ViewportClient->SetBackgroundColor(FLinearColor::Black);

}
void SMiniMapWidget::TestSpawnAcor()
{
	FTransform SpawnPosition(FRotator(0,0,0),FVector(0,0,0),FVector(1));
	APreviewActor * PreviewActor = GetViewportWorld()->SpawnActorDeferred<APreviewActor>(APreviewActor::StaticClass(), SpawnPosition, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (PreviewActor)
	{
		PreviewActor->SetMeshComponent(TEXT("ArmyCenter"));
		PreviewActor->FinishSpawning(SpawnPosition);
	}

}
UWorld * SMiniMapWidget::GetViewportWorld() const
{
	if (PreviewViewport.IsValid())
	{
		return PreviewViewport->PreviewScene.GetWorld();
	}
	return NULL;
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