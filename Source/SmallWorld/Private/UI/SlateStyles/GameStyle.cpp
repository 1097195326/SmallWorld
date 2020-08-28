#include "GameStyle.h"
#include "Slate/SlateGameResources.h"


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
	const FLinearColor DefaultForeground(FColor(0.72f, 0.72f, 0.72f, 1.f));
	const FLinearColor SelectionColor(0.728f, 0.364f, 0.003f);
	const FLinearColor SelectionColor_Pressed(0.701f, 0.225f, 0.003f);
	Style.Set("DefaultForeground", DefaultForeground);
	
	// FontStyle
	// Normal Text
	const FTextBlockStyle NormalText = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 9))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor(FLinearColor(0.02f, 0.3f, 0.0f))
		.SetHighlightShape(BOX_BRUSH("Common/TextBlockHighlightShape", FMargin(3.f / 8.f)));
	const FTextBlockStyle Text_8 = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 8))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);
	const FTextBlockStyle Text_9 = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 9))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);
	const FTextBlockStyle Text_12 = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 12))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);
	const FTextBlockStyle Text_24 = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 24))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);
	const FTextBlockStyle XRText_14_Bold = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Bold", 14))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White))
		.SetShadowOffset(FVector2D::ZeroVector);

	Style.Set("NormalText", NormalText);
	Style.Set("Text_8", Text_8);
	Style.Set("Text_9", Text_9);
	Style.Set("Text_12", Text_12);
	Style.Set("Text_24", Text_24);
	Style.Set("Text_14_Bold", XRText_14_Bold);

	// IconSize
	const FVector2D Icon1x1(1.0f, 1.0f);
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon12x12(12.0f, 12.0f);
	const FVector2D Icon14x14(14.0f, 14.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon128x128(128.0f, 128.0f);
	
	// Texture

	Style.Set("White", new IMAGE_BRUSH(TEXT("White"), Icon1x1, Style.GetColor("Color.FFFFFFFF")));
	Style.Set("BorderBackground", new IMAGE_BRUSH(TEXT("BorderBackground"), FVector2D(384, 128), Style.GetColor("Color.FFFFFFFF")));
	Style.Set("StartBackground", new IMAGE_BRUSH(TEXT("StartBackground"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));

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
	//Style.Set("Icon.ArmyCenter0", new IMAGE_BRUSH(TEXT("IconArmyCenter0"), Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	// Soldier Icon
	/*UTexture2D * IconTexture = nullptr;
	IconTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/Texture/IconArcher"), nullptr);
	Style.Set("Icon.Archer", new FSlateImageBrush(IconTexture, Icon128x128, Style.GetColor("Color.FFFFFFFF")));
	*/

	// Invisible buttons, borders, etc.
	const FButtonStyle NoBorder = FButtonStyle()
		.SetNormal(FSlateNoResource())
		.SetHovered(FSlateNoResource())
		.SetPressed(FSlateNoResource())
		.SetNormalPadding(FMargin(0.0f, 0.0f, 0.0f, 1.0f))
		.SetPressedPadding(FMargin(0.0f, 1.0f, 0.0f, 0.0f));

	// Convenient transparent/invisible elements
	{
		Style.Set("NoBrush", new FSlateNoResource());
		Style.Set("NoBorder", new FSlateNoResource());
		Style.Set("NoBorder.Normal", new FSlateNoResource());
		Style.Set("NoBorder.Hovered", new FSlateNoResource());
		Style.Set("NoBorder.Pressed", new FSlateNoResource());
		Style.Set("NoBorder", NoBorder);
	}
	// SScrollBar defaults...
	const FScrollBarStyle ScrollBar = FScrollBarStyle()
		.SetVerticalTopSlotImage(IMAGE_BRUSH("Common/Scrollbar_Background_Vertical", FVector2D(8, 8)))
		.SetVerticalBottomSlotImage(IMAGE_BRUSH("Common/Scrollbar_Background_Vertical", FVector2D(8, 8)))
		.SetHorizontalTopSlotImage(IMAGE_BRUSH("Common/Scrollbar_Background_Horizontal", FVector2D(8, 8)))
		.SetHorizontalBottomSlotImage(IMAGE_BRUSH("Common/Scrollbar_Background_Horizontal", FVector2D(8, 8)))
		.SetNormalThumbImage(BOX_BRUSH("Common/Scrollbar_Thumb", FMargin(4.f / 16.f)))
		.SetDraggedThumbImage(BOX_BRUSH("Common/Scrollbar_Thumb", FMargin(4.f / 16.f)))
		.SetHoveredThumbImage(BOX_BRUSH("Common/Scrollbar_Thumb", FMargin(4.f / 16.f)));
	// SEditableTextBox defaults...
	const FEditableTextBoxStyle NormalEditableTextBoxStyle = FEditableTextBoxStyle()
		.SetBackgroundImageNormal(BOX_BRUSH("Common/TextBox", FMargin(4.0f / 16.0f)))
		.SetBackgroundImageHovered(BOX_BRUSH("Common/TextBox_Hovered", FMargin(4.0f / 16.0f)))
		.SetBackgroundImageFocused(BOX_BRUSH("Common/TextBox_Hovered", FMargin(4.0f / 16.0f)))
		.SetBackgroundImageReadOnly(BOX_BRUSH("Common/TextBox_ReadOnly", FMargin(4.0f / 16.0f)))
		.SetScrollBarStyle(ScrollBar);
	{
		Style.Set("NormalEditableTextBox", NormalEditableTextBoxStyle);
		// "NormalFont".
	}
	// ButtonStyle
	Style.Set("CommonButton", FButtonStyle()
		.SetNormal(*Style.GetBrush("White"))
		.SetHovered(*Style.GetBrush("White"))
		.SetPressed(*Style.GetBrush("White"))
		.SetNormalPadding(0)
		.SetPressedPadding(0)
	);

	Style.Set("Slider", FSliderStyle()
		.SetNormalBarImage(FSlateColorBrush(FColor::White))
		.SetHoveredBarImage(FSlateColorBrush(FColor::White))
		.SetDisabledBarImage(FSlateColorBrush(FLinearColor::Gray))
		.SetNormalThumbImage(IMAGE_BRUSH("White", FVector2D(8.0f, 14.0f), Style.GetColor("Color.FFFFFFFF")))
		.SetHoveredThumbImage(IMAGE_BRUSH("White", FVector2D(8.0f, 14.0f), Style.GetColor("Color.FFFFFFFF")))
		.SetDisabledThumbImage(IMAGE_BRUSH("White", FVector2D(8.0f, 14.0f), Style.GetColor("Color.FFFFFFFF")))
		.SetBarThickness(2.0f));

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
	
	// MenuBar
	{
		Style.Set("Menu.Background", new BOX_BRUSH("Old/Menu_Background", FMargin(8.0f / 64.0f)));
		Style.Set("Menu.Icon", new IMAGE_BRUSH("Icons/icon_tab_toolbar_16px", Icon16x16));
		Style.Set("Menu.Expand", new IMAGE_BRUSH("Icons/toolbar_expand_16x", Icon16x16));
		Style.Set("Menu.SubMenuIndicator", new IMAGE_BRUSH("Common/SubmenuArrow", Icon8x8));
		Style.Set("Menu.SToolBarComboButtonBlock.Padding", FMargin(4.0f));
		Style.Set("Menu.SToolBarButtonBlock.Padding", FMargin(4.0f));
		Style.Set("Menu.SToolBarCheckComboButtonBlock.Padding", FMargin(4.0f));
		Style.Set("Menu.SToolBarButtonBlock.CheckBox.Padding", FMargin(0.0f));
		Style.Set("Menu.SToolBarComboButtonBlock.ComboButton.Color", DefaultForeground);

		Style.Set("Menu.Block.IndentedPadding", FMargin(18.0f, 2.0f, 4.0f, 4.0f));
		Style.Set("Menu.Block.Padding", FMargin(2.0f, 2.0f, 4.0f, 4.0f));

		Style.Set("Menu.Separator", new BOX_BRUSH("Old/Button", 4.0f / 32.0f));
		Style.Set("Menu.Separator.Padding", FMargin(0.5f));

		Style.Set("Menu.Label", Style.GetWidgetStyle<FTextBlockStyle>("Text_9"));
		Style.Set("Menu.EditableText", FEditableTextBoxStyle(NormalEditableTextBoxStyle).SetFont(TTF_FONT("Fonts/Roboto-Regular", 9)));
		Style.Set("Menu.Keybinding", Style.GetWidgetStyle<FTextBlockStyle>("Text_8"));

		Style.Set("Menu.Heading", FTextBlockStyle(NormalText)
			.SetColorAndOpacity(FLinearColor(0.4f, 0.4, 0.4f, 1.0f)));

		/* Set images for various SCheckBox states associated with menu check box items... */
		const FCheckBoxStyle BasicMenuCheckBoxStyle = FCheckBoxStyle()
			.SetUncheckedImage(IMAGE_BRUSH("Common/SmallCheckBox", Icon14x14))
			.SetUncheckedHoveredImage(IMAGE_BRUSH("Common/SmallCheckBox_Hovered", Icon14x14))
			.SetUncheckedPressedImage(IMAGE_BRUSH("Common/SmallCheckBox_Hovered", Icon14x14, FLinearColor(0.5f, 0.5f, 0.5f)))
			.SetCheckedImage(IMAGE_BRUSH("Common/SmallCheckBox_Checked", Icon14x14))
			.SetCheckedHoveredImage(IMAGE_BRUSH("Common/SmallCheckBox_Checked_Hovered", Icon14x14))
			.SetCheckedPressedImage(IMAGE_BRUSH("Common/SmallCheckBox_Checked_Hovered", Icon14x14, FLinearColor(0.5f, 0.5f, 0.5f)))
			.SetUndeterminedImage(IMAGE_BRUSH("Common/CheckBox_Undetermined", Icon14x14))
			.SetUndeterminedHoveredImage(IMAGE_BRUSH("Common/CheckBox_Undetermined_Hovered", Icon14x14))
			.SetUndeterminedPressedImage(IMAGE_BRUSH("Common/CheckBox_Undetermined_Hovered", Icon14x14, FLinearColor(0.5f, 0.5f, 0.5f)));

		/* ...and add the new style */
		Style.Set("Menu.CheckBox", BasicMenuCheckBoxStyle);

		/* Read-only checkbox that appears next to a menu item */
		/* Set images for various SCheckBox states associated with read-only menu check box items... */
		const FCheckBoxStyle BasicMenuCheckStyle = FCheckBoxStyle()
			.SetUncheckedImage(IMAGE_BRUSH("Icons/Empty_14x", Icon14x14))
			.SetUncheckedHoveredImage(IMAGE_BRUSH("Icons/Empty_14x", Icon14x14))
			.SetUncheckedPressedImage(IMAGE_BRUSH("Common/SmallCheckBox_Hovered", Icon14x14))
			.SetCheckedImage(IMAGE_BRUSH("Common/SmallCheck", Icon14x14))
			.SetCheckedHoveredImage(IMAGE_BRUSH("Common/SmallCheck", Icon14x14))
			.SetCheckedPressedImage(IMAGE_BRUSH("Common/SmallCheck", Icon14x14))
			.SetUndeterminedImage(IMAGE_BRUSH("Icons/Empty_14x", Icon14x14))
			.SetUndeterminedHoveredImage(FSlateNoResource())
			.SetUndeterminedPressedImage(FSlateNoResource());

		/* ...and add the new style */
		Style.Set("Menu.Check", BasicMenuCheckStyle);

		/* This radio button is actually just a check box with different images */
		/* Set images for various Menu radio button (SCheckBox) states... */
		const FCheckBoxStyle BasicMenuRadioButtonStyle = FCheckBoxStyle()
			.SetUncheckedImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16))
			.SetUncheckedHoveredImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16))
			.SetUncheckedPressedImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16))
			.SetCheckedImage(IMAGE_BRUSH("Common/RadioButton_Selected_16x", Icon16x16))
			.SetCheckedHoveredImage(IMAGE_BRUSH("Common/RadioButton_Selected_16x", Icon16x16, SelectionColor))
			.SetCheckedPressedImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16, SelectionColor_Pressed))
			.SetUndeterminedImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16))
			.SetUndeterminedHoveredImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16, SelectionColor))
			.SetUndeterminedPressedImage(IMAGE_BRUSH("Common/RadioButton_Unselected_16x", Icon16x16, SelectionColor_Pressed));

		/* ...and set new style */
		Style.Set("Menu.RadioButton", BasicMenuRadioButtonStyle);

		/* Create style for "Menu.ToggleButton" widget ... */
		const FCheckBoxStyle MenuToggleButtonCheckBoxStyle = FCheckBoxStyle()
			.SetCheckBoxType(ESlateCheckBoxType::ToggleButton)
			.SetUncheckedImage(FSlateNoResource())
			.SetUncheckedPressedImage(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor_Pressed))
			.SetUncheckedHoveredImage(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor))
			.SetCheckedImage(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor_Pressed))
			.SetCheckedHoveredImage(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor_Pressed))
			.SetCheckedPressedImage(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor));
		/* ... and add new style */
		Style.Set("Menu.ToggleButton", MenuToggleButtonCheckBoxStyle);

		Style.Set("Menu.Button", FButtonStyle(NoBorder)
			.SetNormal(FSlateNoResource())
			.SetPressed(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor_Pressed))
			.SetHovered(BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor))
			.SetNormalPadding(FMargin(0, 1))
			.SetPressedPadding(FMargin(0, 2, 0, 0))
		);

		Style.Set("Menu.Button.Checked", new BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor_Pressed));
		Style.Set("Menu.Button.Checked_Hovered", new BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor_Pressed));
		Style.Set("Menu.Button.Checked_Pressed", new BOX_BRUSH("Common/RoundedSelection_16x", 4.0f / 16.0f, SelectionColor));

		/* The style of a menu bar button when it has a sub menu open */
		Style.Set("Menu.Button.SubMenuOpen", new BORDER_BRUSH("Common/Selection", FMargin(4.f / 16.f), FLinearColor(0.10f, 0.10f, 0.10f)));
	}
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