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
	
	//Style.Set()

	return StyleSet;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT
const ISlateStyle& FGameStyle::Get()
{
	return *GameStyleInstance;
}