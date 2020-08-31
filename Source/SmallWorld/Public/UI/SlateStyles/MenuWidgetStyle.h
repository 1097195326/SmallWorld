//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NameTypes.h"
//#include "UObject/ObjectMacros.h"
//#include "Layout/Margin.h"
//#include "Sound/SlateSound.h"
//#include "Styling/SlateColor.h"
//#include "Styling/SlateBrush.h"
//#include "Styling/SlateWidgetStyle.h"
//#include "Styling/SlateWidgetStyleContainerBase.h"
//
//#include "MenuWidgetStyle.generated.h"
//
//
//
//UENUM()
//namespace MenuLayoutType
//{
//	enum Type
//	{
//		/* Single one page menu. */
//		Single,
//		/* Side by side menu. Main menu on left, any sub menu on right. */
//		SideBySide
//	};
//}
//
//USTRUCT()
//struct FMenuStyle : public FSlateWidgetStyle
//{
//	GENERATED_USTRUCT_BODY()
//
//		FMenuStyle();
//	virtual ~FMenuStyle();
//
//	// FSlateWidgetStyle
//	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
//	static const FName TypeName;
//	virtual const FName GetTypeName() const override { return TypeName; };
//	static const FMenuStyle& GetDefault();
//
//	/**
//	 * The brush used to draw the top of the menu
//	 */
//	UPROPERTY(EditAnywhere, Category = Brushes)
//		FSlateBrush MenuTopBrush;
//	FMenuStyle& SetMenuTopBrush(const FSlateBrush& InMenuTopBrush) { MenuTopBrush = InMenuTopBrush; return *this; }
//
//	/**
//	 * The brush used to draw the menu border
//	 */
//	UPROPERTY(EditAnywhere, Category = Brushes)
//		FSlateBrush MenuFrameBrush;
//	FMenuStyle& SetMenuFrameBrush(const FSlateBrush& InMenuFrameBrush) { MenuFrameBrush = InMenuFrameBrush; return *this; }
//
//	/**
//	* The brush used to draw the menu background
//	*/
//	UPROPERTY(EditAnywhere, Category = Brushes)
//		FSlateBrush MenuBackgroundBrush;
//	FMenuStyle& SetMenuBackgroundBrush(const FSlateBrush& InMenuBackgroundBrush) { MenuBackgroundBrush = InMenuBackgroundBrush; return *this; }
//
//	/**
//	 * The brush used to draw the selected menu item
//	 */
//	UPROPERTY(EditAnywhere, Category = Brushes)
//		FSlateBrush MenuSelectBrush;
//	FMenuStyle& SetMenuSelectBrush(const FSlateBrush& InMenuSelectBrush) { MenuSelectBrush = InMenuSelectBrush; return *this; }
//
//	/**
//	 * The sound the menu should play when entering a sub-menu
//	 */
//	UPROPERTY(EditAnywhere, Category = Sound)
//		FSlateSound MenuEnterSound;
//	FMenuStyle& SetMenuEnterSound(const FSlateSound& InMenuEnterSound) { MenuEnterSound = InMenuEnterSound; return *this; }
//
//	/**
//	 * The sound the menu should play when returning to a parent menu
//	 */
//	UPROPERTY(EditAnywhere, Category = Sound)
//		FSlateSound MenuBackSound;
//	FMenuStyle& SetMenuBackSound(const FSlateSound& InMenuBackSound) { MenuBackSound = InMenuBackSound; return *this; }
//
//	/**
//	 * The sound the menu should play when a menu option is changed
//	 */
//	UPROPERTY(EditAnywhere, Category = Sound)
//		FSlateSound OptionChangeSound;
//	FMenuStyle& SetOptionChangeSound(const FSlateSound& InOptionChangeSound) { OptionChangeSound = InOptionChangeSound; return *this; }
//
//	/**
//	 * The sound the menu should play when the selected menu item is changed
//	 */
//	UPROPERTY(EditAnywhere, Category = Sound)
//		FSlateSound MenuItemChangeSound;
//	FMenuStyle& SetMenuItemChangeSound(const FSlateSound& InMenuItemChangeSound) { MenuItemChangeSound = InMenuItemChangeSound; return *this; }
//
//	/**
//	 * The sound the menu should play when the selected menu item is disabled or unbound
//	 */
//	UPROPERTY(EditAnywhere, Category = Sound)
//		FSlateSound MenuItemInactiveSound;
//	FMenuStyle& SetMenuItemInactiveSound(const FSlateSound& InMenuItemInactiveSound) { MenuItemInactiveSound = InMenuItemInactiveSound; return *this; }
//
//	/**
//	 * The sound the menu should play when the selected menu item is chosen
//	 */
//	UPROPERTY(EditAnywhere, Category = Sound)
//		FSlateSound MenuItemChosenSound;
//	FMenuStyle& SetMenuItemChosenSound(const FSlateSound& InMenuItemChosenSound) { MenuItemChosenSound = InMenuItemChosenSound; return *this; }
//
//	/**
//	 * The left hand margin for the main menu
//	 */
//	UPROPERTY(EditAnywhere, Category = Layout)
//		float LeftMarginPercent;
//	FMenuStyle& SetMenuLeftMarginPercent(const float InLeftMarginPercent) { LeftMarginPercent = InLeftMarginPercent; return *this; }
//
//	/**
//	* The left hand margin for the sub menu
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		float SubMenuMarginPercent;
//	FMenuStyle& SetSubMenuMarginPercent(const float InSubMenuMarginPercent) { SubMenuMarginPercent = InSubMenuMarginPercent; return *this; }
//
//	/**
//	* Layout type.
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		TEnumAsByte<MenuLayoutType::Type> LayoutType;
//	FMenuStyle& SetMenuTitleColor(const MenuLayoutType::Type InLayoutType) { LayoutType = InLayoutType; return *this; }
//
//	/**
//	* Title border margin.
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		FMargin TitleBorderMargin;
//	FMenuStyle& SetTitleBorderMargin(const FMargin InTitleBorderMargin) { TitleBorderMargin = InTitleBorderMargin; return *this; }
//
//	/**
//	* Item border margin.
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		FMargin ItemBorderMargin;
//	FMenuStyle& SetItemBorderMargin(const FMargin InItemBorderMargin) { ItemBorderMargin = InItemBorderMargin; return *this; }
//
//	/**
//	* Title horizontal alignment.
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		TEnumAsByte<EHorizontalAlignment> TitleHorizontalAlignment;
//	FMenuStyle& SetTitleHorizontalAlignment(const EHorizontalAlignment InTitleHorizontalAlignment) { TitleHorizontalAlignment = InTitleHorizontalAlignment; return *this; }
//
//	/**
//	* Title vertical alignment.
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		TEnumAsByte<EVerticalAlignment> TitleVerticalAlignment;
//	FMenuStyle& SetTitleVerticalAlignment(const EVerticalAlignment InTitleVerticalAlignment) { TitleVerticalAlignment = InTitleVerticalAlignment; return *this; }
//
//	/**
//	* Panel vertical alignment.
//	*/
//	UPROPERTY(EditAnywhere, Category = Layout)
//		TEnumAsByte<EVerticalAlignment> PanelsVerticalAlignment;
//	FMenuStyle& SetPanelsVerticalAlignment(const EVerticalAlignment InPanelsVerticalAlignment) { PanelsVerticalAlignment = InPanelsVerticalAlignment; return *this; }
//
//	/**
//	 * Speed at which the menu initially appears.
//	 */
//	UPROPERTY(EditAnywhere, Category = Animation)
//		float AnimationSpeed;
//	FMenuStyle& SetMainAnimDuration(const float InAnimationSpeed) { AnimationSpeed = InAnimationSpeed; return *this; }
//
//	/**
//	* Color of the text.
//	*/
//	UPROPERTY(EditAnywhere, Category = Color)
//		FSlateColor TextColor;
//	FMenuStyle& SetTextColor(const FSlateColor InTextColor) { TextColor = InTextColor; return *this; }
//};
//
//
//UCLASS(hidecategories = Object, MinimalAPI)
//class UMenuWidgetStyle : public USlateWidgetStyleContainerBase
//{
//	GENERATED_UCLASS_BODY()
//
//public:
//	/** The actual data describing the menu's appearance. */
//	UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))
//	FMenuStyle MenuStyle;
//
//	virtual const struct FSlateWidgetStyle* const GetStyle() const override
//	{
//		return static_cast<const struct FSlateWidgetStyle*>(&MenuStyle);
//	}
//};
