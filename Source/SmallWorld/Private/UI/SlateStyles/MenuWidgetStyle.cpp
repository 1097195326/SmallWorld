//#include "MenuWidgetStyle.h"
//
//
//FMenuStyle::FMenuStyle()
//{
//	LeftMarginPercent = 0.1f;
//	SubMenuMarginPercent = 0.02f;
//	AnimationSpeed = 0.2f;
//	TextColor = FLinearColor::White;
//	LayoutType = MenuLayoutType::Single;
//
//	TitleHorizontalAlignment = HAlign_Center;
//	TitleVerticalAlignment = VAlign_Bottom;
//	PanelsVerticalAlignment = VAlign_Center;
//}
//
//FMenuStyle::~FMenuStyle()
//{
//}
//
//const FName FMenuStyle::TypeName(TEXT("FMenuStyle"));
//
//const FMenuStyle& FMenuStyle::GetDefault()
//{
//	static FMenuStyle Default;
//	return Default;
//}
//
//void FMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
//{
//	OutBrushes.Add(&MenuTopBrush);
//	OutBrushes.Add(&MenuFrameBrush);
//	OutBrushes.Add(&MenuBackgroundBrush);
//	OutBrushes.Add(&MenuSelectBrush);
//}
//
//
//
//UMenuWidgetStyle::UMenuWidgetStyle(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//
//}