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
	Style.Set("Color.7F6E6F70", FLinearColor(FColor(0X7F6E6F70)));//black-3
	Style.Set("Color.4C6E6F70", FLinearColor(FColor(0X4C6E6F70)));//black-3
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
	const FVector2D Icon128x128(128.0f, 128.0f);
	
	// Texture
	// 
	Style.Set("Icon.Clear", new IMAGE_BRUSH(TEXT("Icon_Clear"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Rotation", new IMAGE_BRUSH(TEXT("Icon_Rotation"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Move", new IMAGE_BRUSH(TEXT("Icon_Move"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Upgrade", new IMAGE_BRUSH(TEXT("Icon_Upgrade"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Power", new IMAGE_BRUSH(TEXT("Icon_Power"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Hero", new IMAGE_BRUSH(TEXT("Icon_Hero"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Map", new IMAGE_BRUSH(TEXT("Icon_Map"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Menu", new IMAGE_BRUSH(TEXT("Icon_Menu"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	//Building Icon 
	Style.Set("Icon.ArmyCenter0", new IMAGE_BRUSH(TEXT("IconArmyCenter0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.ArmyCenter1", new IMAGE_BRUSH(TEXT("IconArmyCenter1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.ArmyCenter2", new IMAGE_BRUSH(TEXT("IconArmyCenter2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery0", new IMAGE_BRUSH(TEXT("IconBakery0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery1", new IMAGE_BRUSH(TEXT("IconBakery0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery2", new IMAGE_BRUSH(TEXT("IconBakery0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Bakery3", new IMAGE_BRUSH(TEXT("IconBakery3"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter0", new IMAGE_BRUSH(TEXT("IconCommandCenter0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter1", new IMAGE_BRUSH(TEXT("IconCommandCenter1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter2", new IMAGE_BRUSH(TEXT("IconCommandCenter2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.CommandCenter3", new IMAGE_BRUSH(TEXT("IconCommandCenter3"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Farm0", new IMAGE_BRUSH(TEXT("IconFarm0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Farm1", new IMAGE_BRUSH(TEXT("IconFarm1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Farm2", new IMAGE_BRUSH(TEXT("IconFarm2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FoodStore0", new IMAGE_BRUSH(TEXT("IconFoodStore0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FoodStore1", new IMAGE_BRUSH(TEXT("IconFoodStore1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FoodStore2", new IMAGE_BRUSH(TEXT("IconFoodStore2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FruitFarm0", new IMAGE_BRUSH(TEXT("IconFruitFarm0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FruitFarm1", new IMAGE_BRUSH(TEXT("IconFruitFarm1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.FruitFarm2", new IMAGE_BRUSH(TEXT("IconFruitFarm2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Gate0", new IMAGE_BRUSH(TEXT("IconGate0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Gate1", new IMAGE_BRUSH(TEXT("IconGate1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Gate2", new IMAGE_BRUSH(TEXT("IconGate2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.House0", new IMAGE_BRUSH(TEXT("IconHouse0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.House1", new IMAGE_BRUSH(TEXT("IconHouse1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.House2", new IMAGE_BRUSH(TEXT("IconHouse2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Mill0", new IMAGE_BRUSH(TEXT("IconMill0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Mill1", new IMAGE_BRUSH(TEXT("IconMill1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Mill2", new IMAGE_BRUSH(TEXT("IconMill2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.MoneyStore0", new IMAGE_BRUSH(TEXT("IconMoneyStore0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.MoneyStore1", new IMAGE_BRUSH(TEXT("IconMoneyStore1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.MoneyStore2", new IMAGE_BRUSH(TEXT("IconMoneyStore2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.WoodStoneStore0", new IMAGE_BRUSH(TEXT("IconWoodStoneStore0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Tower0", new IMAGE_BRUSH(TEXT("IconTower0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Tower1", new IMAGE_BRUSH(TEXT("IconTower1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Tower2", new IMAGE_BRUSH(TEXT("IconTower2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Wall0", new IMAGE_BRUSH(TEXT("IconWall0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Wall1", new IMAGE_BRUSH(TEXT("IconWall1"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("Icon.Wall2", new IMAGE_BRUSH(TEXT("IconWall2"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	// Soldier Icon
	UTexture2D * IconTexture = nullptr;
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconArcher"), nullptr);
	Style.Set("Icon.Archer", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconFootman"), nullptr);
	Style.Set("Icon.Footman", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconGriffin"), nullptr);
	Style.Set("Icon.Griffin", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconHorseman"), nullptr);
	Style.Set("Icon.Horseman", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconKnight"), nullptr);
	Style.Set("Icon.Knight", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconMage"), nullptr);
	Style.Set("Icon.Mage", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconPeasant"), nullptr);
	Style.Set("Icon.Peasant", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconSiegeEngine"), nullptr);
	Style.Set("Icon.SiegeEngine", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));




	// ButtonStyle
	Style.Set("MainView.Button.Clear", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Clear"))
		.SetHovered(*Style.GetBrush("Icon.Clear"))
		.SetPressed(*Style.GetBrush("Icon.Clear"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
	Style.Set("MainView.Button.Rotation", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Rotation"))
		.SetHovered(*Style.GetBrush("Icon.Rotation"))
		.SetPressed(*Style.GetBrush("Icon.Rotation"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
	Style.Set("MainView.Button.Move", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Move"))
		.SetHovered(*Style.GetBrush("Icon.Move"))
		.SetPressed(*Style.GetBrush("Icon.Move"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
	Style.Set("MainView.Button.Upgrade", FButtonStyle()
		.SetNormal(*Style.GetBrush("Icon.Upgrade"))
		.SetHovered(*Style.GetBrush("Icon.Upgrade"))
		.SetPressed(*Style.GetBrush("Icon.Upgrade"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);
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