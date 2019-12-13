#include "MainViewUIController.h"



TSharedPtr<SWidget> MainViewUIController::MakeTopLeftWidget()
{
	return 
	SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeTopCenterWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeTopRightWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeMiddleLeftWidget()
{
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>		MainViewUIController::MakeMiddleCenterWidget()
{
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeMiddleRightWidget()
{
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomLeftWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomCenterWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomRightWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}