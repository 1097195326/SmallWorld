#include "GameStyle.h"
#include "SlateGameResources.h"


TSharedPtr<ISlateStyle> FGameStyle::GameStyleInstance = nullptr;

void FGameStyle::Startup()
{
	if (!GameStyleInstance)
	{
		GameStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*GameStyleInstance);
	}
}
void FGameStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*GameStyleInstance);
	GameStyleInstance.Reset();
}
FName FGameStyle::GetStyleName()
{
	static FName  StyleName(TEXT("GameStyle"));
	return StyleName;
}


#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::ProjectContentDir() / "UI/Texture"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::ProjectContentDir() / "UI/Texture"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::ProjectContentDir() / "UI/Texture"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate")/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate")/ RelativePath + TEXT(".otf"), __VA_ARGS__ )

TSharedRef<FSlateStyleSet> FGameStyle::Create()
{
	TSharedRef< FSlateStyleSet> StyleSet = FSlateGameResources::New(GetStyleName(), TEXT("/Game/UI/Slate"), TEXT("/Game/UI/Slate"));
	FSlateStyleSet & Style = StyleSet.Get();
	// Color
	Style.Set("Color.None", FLinearColor(FColor(0X00000000)));
	Style.Set("Color.FFFFE0B2", FLinearColor(FColor(0XFFFFE0B2)));//orange-1
	Style.Set("Color.FFFFB74D", FLinearColor(FColor(0XFFFFB74D)));//orange-2
	Style.Set("Color.FFFFA726", FLinearColor(FColor(0XFFFFA726)));//orange-3
	Style.Set("Color.FFFF9800", FLinearColor(FColor(0XFFFF9800)));//orange-4
	Style.Set("Color.FFFB8C00", FLinearColor(FColor(0XFFFB8C00)));//orange-5

	Style.Set("Color.FFFA4147", FLinearColor(FColor(0XFFFA4147)));//red
	Style.Set("Color.FF23DB73", FLinearColor(FColor(0XFF23DB73)));//green
	Style.Set("Color.FFFFF700", FLinearColor(FColor(0XFFFFF700)));//yellow
	Style.Set("Color.FF00FFFF", FLinearColor(FColor(0XFF00FFFF)));//blue
	Style.Set("Color.FFE605E6", FLinearColor(FColor(0XFFE605E6)));//purple

	Style.Set("Color.FFFFFFFF", FLinearColor(FColor(0XFFFFFFFF)));//white

	Style.Set("Color.FFE1E2E6", FLinearColor(FColor(0XFFE1E2E6)));//black-1
	Style.Set("Color.FFAFB0B3", FLinearColor(FColor(0XFFAFB0B3)));//black-2
	Style.Set("Color.FF6E6F70", FLinearColor(FColor(0XFF6E6F70)));//black-3
	Style.Set("Color.FF424447", FLinearColor(FColor(0XFF424447)));//black-4
	Style.Set("Color.FF383A3D", FLinearColor(FColor(0XFF383A3D)));//black-5
	Style.Set("Color.FF2F3033", FLinearColor(FColor(0XFF2F3033)));//black-6
	Style.Set("Color.FF2A2B2E", FLinearColor(FColor(0XFF2A2B2E)));//black-7
	Style.Set("Color.FF212224", FLinearColor(FColor(0XFF212224)));//black-8
	Style.Set("Color.FF1C1D1F", FLinearColor(FColor(0XFF1C1D1F)));//black-9
	
	// FontStyle
	const FTextBlockStyle Text_12 = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 12))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);

	const FTextBlockStyle XRText_14_Bold = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Bold", 14))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);

	Style.Set("Text_12", Text_12);
	Style.Set("Text_14_Bold", XRText_14_Bold);

	// IconSize
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	
	// Texture
	Style.Set("Icon.Power",new IMAGE_BRUSH(TEXT("Icon_Power"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Hero", new IMAGE_BRUSH(TEXT("Icon_Hero"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Map", new IMAGE_BRUSH(TEXT("Icon_Map"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Menu", new IMAGE_BRUSH(TEXT("Icon_Menu"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	
	Style.Set("Icon.ArmyCenter0", new IMAGE_BRUSH(TEXT("IconArmyCenter0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.ArmyCenter1", new IMAGE_BRUSH(TEXT("IconArmyCenter1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.ArmyCenter2", new IMAGE_BRUSH(TEXT("IconArmyCenter2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery0", new IMAGE_BRUSH(TEXT("IconBakery0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery1", new IMAGE_BRUSH(TEXT("IconBakery0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery2", new IMAGE_BRUSH(TEXT("IconBakery0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery3", new IMAGE_BRUSH(TEXT("IconBakery3"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter0", new IMAGE_BRUSH(TEXT("IconCommandCenter0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter1", new IMAGE_BRUSH(TEXT("IconCommandCenter1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter2", new IMAGE_BRUSH(TEXT("IconCommandCenter2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter3", new IMAGE_BRUSH(TEXT("IconCommandCenter3"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Farm0", new IMAGE_BRUSH(TEXT("IconFarm0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Farm1", new IMAGE_BRUSH(TEXT("IconFarm1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Farm2", new IMAGE_BRUSH(TEXT("IconFarm2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FoodStore0", new IMAGE_BRUSH(TEXT("IconFoodStore0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FoodStore1", new IMAGE_BRUSH(TEXT("IconFoodStore1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FoodStore2", new IMAGE_BRUSH(TEXT("IconFoodStore2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FruitFarm0", new IMAGE_BRUSH(TEXT("IconFruitFarm0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FruitFarm1", new IMAGE_BRUSH(TEXT("IconFruitFarm1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FruitFarm2", new IMAGE_BRUSH(TEXT("IconFruitFarm2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Gate0", new IMAGE_BRUSH(TEXT("IconGate0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Gate1", new IMAGE_BRUSH(TEXT("IconGate1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Gate2", new IMAGE_BRUSH(TEXT("IconGate2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.House0", new IMAGE_BRUSH(TEXT("IconHouse0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.House1", new IMAGE_BRUSH(TEXT("IconHouse1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.House2", new IMAGE_BRUSH(TEXT("IconHouse2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Mill0", new IMAGE_BRUSH(TEXT("IconMill0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Mill1", new IMAGE_BRUSH(TEXT("IconMill1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Mill2", new IMAGE_BRUSH(TEXT("IconMill2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.MoneyStore0", new IMAGE_BRUSH(TEXT("IconMoneyStore0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.MoneyStore1", new IMAGE_BRUSH(TEXT("IconMoneyStore1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.MoneyStore2", new IMAGE_BRUSH(TEXT("IconMoneyStore2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.WoodStoneStore0", new IMAGE_BRUSH(TEXT("IconWoodStoneStore0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Tower0", new IMAGE_BRUSH(TEXT("IconTower0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Tower1", new IMAGE_BRUSH(TEXT("IconTower1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Tower2", new IMAGE_BRUSH(TEXT("IconTower2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Wall0", new IMAGE_BRUSH(TEXT("IconWall0"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Wall1", new IMAGE_BRUSH(TEXT("IconWall1"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Wall2", new IMAGE_BRUSH(TEXT("IconWall2"), FVector2D(100, 100), Style.GetColor("Color.FFFFFFFF")));



	// ButtonStyle
	Style.Set("MainView.Button.Power", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Power"))
		.SetHovered(*Style.GetBrush("Icon.Power"))
		.SetPressed(*Style.GetBrush("Icon.Power"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
	Style.Set("MainView.Button.Hero", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Hero"))
		.SetHovered(*Style.GetBrush("Icon.Hero"))
		.SetPressed(*Style.GetBrush("Icon.Hero"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
	Style.Set("MainView.Button.Map", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Map"))
		.SetHovered(*Style.GetBrush("Icon.Map"))
		.SetPressed(*Style.GetBrush("Icon.Map"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
	Style.Set("MainView.Button.Menu", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Menu"))
		.SetHovered(*Style.GetBrush("Icon.Menu"))
		.SetPressed(*Style.GetBrush("Icon.Menu"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);

	return StyleSet;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT
 ISlateStyle& FGameStyle::Get()
{
	return *GameStyleInstance;
}