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
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectContentDir() / "UI/Font"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectContentDir() / "UI/Font"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )

TSharedRef<FSlateStyleSet> FGameStyle::Create()
{
	TSharedRef< FSlateStyleSet> StyleSet = FSlateGameResources::New(GetStyleName(), TEXT("/Game/UI/Slate"), TEXT("/Game/UI/Slate"));
	FSlateStyleSet & Style = StyleSet.Get();
	// Color
	Style.Set("Color.None", FLinearColor(FColor(0X00000000)));
	Style.Set("Color.FF191A1D", FLinearColor(FColor(0XFF191A1D)));
	Style.Set("Color.489D9FA5", FLinearColor(FColor(0X489D9FA5)));
	Style.Set("Color.21FFFFFF", FLinearColor(FColor(0X21FFFFFF)));
	Style.Set("Color.99000000", FLinearColor(FColor(0X99000000)));
	Style.Set("Color.7F000000", FLinearColor(FColor(0X7F000000)));
	
	// IconSize
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	
	// Texture
	UTexture2D * Texture = nullptr;
	
	Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/UI/Texture/Icon_Power")));
	Style.Set("Icon.Power", new FSlateDynamicImageBrush(Texture,FVector2D(100, 100),NAME_None));
	Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/UI/Texture/Icon_Hero")));
	Style.Set("Icon.Hero", new FSlateDynamicImageBrush(Texture, FVector2D(100, 100), NAME_None));
	Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/UI/Texture/Icon_Map")));
	Style.Set("Icon.Map", new FSlateDynamicImageBrush(Texture, FVector2D(100, 100), NAME_None));
	Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/UI/Texture/Icon_Menu")));
	Style.Set("Icon.Menu", new FSlateDynamicImageBrush(Texture, FVector2D(100, 100), NAME_None));
	
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