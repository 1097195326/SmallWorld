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
	
	Style.Set("Color.None", FLinearColor(FColor(0X00000000)));
	Style.Set("Color.FF191A1D", FLinearColor(FColor(0XFF191A1D)));
	Style.Set("Color.FF28292B", FLinearColor(FColor(0XFF28292B)));
	Style.Set("Color.FF343539", FLinearColor(FColor(0XFF343539)));
	Style.Set("Color.FF353535", FLinearColor(FColor(0XFF353535)));
	Style.Set("Color.FF4C4D52", FLinearColor(FColor(0XFF4C4D52)));
	Style.Set("Color.FF656870", FLinearColor(FColor(0XFF656870)));
	Style.Set("Color.489D9FA5", FLinearColor(FColor(0X489D9FA5)));
	Style.Set("Color.FF9D9FA5", FLinearColor(FColor(0XFF9D9FA5)));
	Style.Set("Color.FF313236", FLinearColor(FColor(0XFF313236)));
	Style.Set("Color.FFFD9800", FLinearColor(FColor(0XFFFD9800)));
	Style.Set("Color.FFFF5A5A", FLinearColor(FColor(0XFFFF5A5A)));
	Style.Set("InputBox.Gray", FLinearColor(FColor(0X21FFFFFF)));
	Style.Set("Color.FF404040", FLinearColor(FColor(0XFF404040)));
	Style.Set("Color.FF353638", FLinearColor(FColor(0XFF353638)));
	Style.Set("Color.FF3F4042", FLinearColor(FColor(0XFF3F4042)));
	Style.Set("Color.FF494A4D", FLinearColor(FColor(0XFF494A4D)));
	Style.Set("Color.FF2F3033", FLinearColor(FColor(0XFF2F3033)));
	Style.Set("Color.FF252629", FLinearColor(FColor(0XFF252629)));
	Style.Set("Color.FF1C1D1F", FLinearColor(FColor(0XFF1C1D1F)));
	Style.Set("Color.FF262729", FLinearColor(FColor(0XFF262729)));
	Style.Set("Color.FF46474D", FLinearColor(FColor(0XFF46474D)));
	Style.Set("Color.99000000", FLinearColor(FColor(0X99000000)));
	Style.Set("Color.FF2B2B2C", FLinearColor(FColor(0XFF2B2B2C)));
	Style.Set("Color.Gray.FF212224", FLinearColor(FColor(0XFF212224)));
	Style.Set("Color.Gray.FF2A2B2E", FLinearColor(FColor(0XFF2A2B2E)));
	Style.Set("Color.FF1C1D1E", FLinearColor(FColor(0XFF1C1D1E)));
	Style.Set("Color.FF343538", FLinearColor(FColor(0XFF343538)));
	Style.Set("Color.FFB5B7BE", FLinearColor(FColor(0XFFB5B7BE)));
	Style.Set("Color.Gray.FFC8C9CC", FLinearColor(FColor(0XFFC8C9CC)));
	Style.Set("Color.FFFF9800", FLinearColor(FColor(0XFFFF9800)));
	Style.Set("Color.FF7AAAEF", FLinearColor(FColor(0XFF7AAAEF)));
	Style.Set("Color.FFF6DDDD", FLinearColor(FColor(0XFFF6DDDD)));
	Style.Set("Color.FF383A3D", FLinearColor(FColor(0XFF383A3D)));
	Style.Set("Color.FF35373B", FLinearColor(FColor(0XFF35373B)));
	Style.Set("Color.FF2E2F32", FLinearColor(FColor(0XFF2E2F32)));
	Style.Set("Color.FF969799", FLinearColor(FColor(0XFF969799)));
	Style.Set("Color.FF232529", FLinearColor(FColor(0XFF232529)));
	Style.Set("Color.FF26272B", FLinearColor(FColor(0XFF26272B)));
	Style.Set("Color.FF1D1E21", FLinearColor(FColor(0XFF1D1E21)));
	Style.Set("Color.FF36373B", FLinearColor(FColor(0XFF36373B)));
	Style.Set("Color.FF333438", FLinearColor(FColor(0XFF333438)));
	Style.Set("Color.FF3C3D42", FLinearColor(FColor(0XFF3C3D42)));
	Style.Set("Color.FF4D4E52", FLinearColor(FColor(0XFF4D4E52)));
	Style.Set("Color.FF65676B", FLinearColor(FColor(0XFF65676B)));
	Style.Set("Color.FF3C3D42", FLinearColor(FColor(0XFF3C3D42)));
	Style.Set("Color.Capture", FLinearColor(FColor(0XFF00FFFF)));
	Style.Set("Color.FF7D7F85", FLinearColor(FColor(0XFF7D7F85)));
	Style.Set("Color.FF8BC7A2", FLinearColor(FColor(0XFF8BC7A2)));
	Style.Set("Color.FF2A2E2F", FLinearColor(FColor(0XFF2A2E2F)));
	Style.Set("Color.FFFF8080", FLinearColor(FColor(0XFFFF8080)));
	Style.Set("Color.FF2E2C2F", FLinearColor(FColor(0XFF2E2C2F)));
	Style.Set("Color.FF5D5F66", FLinearColor(FColor(0XFF5D5F66)));
	Style.Set("Color.FFFF8C00", FLinearColor(FColor(0XFFFF8C00)));
	Style.Set("Color.FFFF8400", FLinearColor(FColor(0XFFFF8400)));
	Style.Set("Color.FFE6E6E6", FLinearColor(FColor(0XFFE6E6E6)));
	Style.Set("Color.FFCB00FF", FLinearColor(FColor(0XFFCB00FF)));
	Style.Set("Color.E5E6E8FF", FLinearColor(FColor(0XE5E6E8FF)));
	Style.Set("Color.FF54555C", FLinearColor(FColor(0XFF54555C)));
	Style.Set("Color.FF666666", FLinearColor(FColor(0XFF666666)));
	Style.Set("Color.FF7D7E80", FLinearColor(FColor(0XFF7D7E80)));
	Style.Set("Color.FF38393D", FLinearColor(FColor(0XFF38393D)));
	Style.Set("Color.FF43444A", FLinearColor(FColor(0XFF43444A)));
	Style.Set("Color.FF0072D6", FLinearColor(FColor(0XFF0072D6)));
	Style.Set("Color.Gray.FF424447", FLinearColor(FColor(0XFF424447)));
	Style.Set("Color.FF585B61", FLinearColor(FColor(0XFF585B61)));
	Style.Set("Color.FFFF4457", FLinearColor(FColor(0XFFFF4457)));
	Style.Set("Color.FF4B4D52", FLinearColor(FColor(0xFF4B4D52)));
	Style.Set("Color.FFF4AD16", FLinearColor(FColor(0XFFF4AD16)));
	Style.Set("Color.Gray.FF111111", FLinearColor(FColor(0XFF111111)));
	Style.Set("Color.FFDC143C", FLinearColor(FColor(0XFFDC143C)));
	Style.Set("Color.Translucent.7F000000", FLinearColor(FColor(0X7F000000)));
	Style.Set("Color.FF212226", FLinearColor(FColor(0XFF212226)));
	Style.Set("Color.FF212224", FLinearColor(FColor(0XFF222124)));
	Style.Set("Color.FF090A0A", FLinearColor(FColor(0XFF090A0A)));
	Style.Set("Color.FFFFC266", FLinearColor(FColor(0XFFFFC266)));
	Style.Set("Color.FF646566", FLinearColor(FColor(0XFF646566)));
	Style.Set("Color.FFF75555", FLinearColor(FColor(0XFFF75555)));
	Style.Set("Color.FFFFB74D", FLinearColor(FColor(0XFFFFB74D)));

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