#pragma once
#include "SWrapCompoundWidget.h"

class SBuildSoldierOperation: public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildSoldierOperation){}

	SLATE_ATTRIBUTE(FText,InShowText)
	SLATE_ATTRIBUTE(FString,InButtonText)
	//SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	void OnValueChange(float InValue);
	void OnTextChange(const FText& InText);

	TAttribute<FText> ShowText;
	TAttribute<FString> ButtonShowText;
	TSharedPtr<SEditableTextBox>	InputNumTextBox;

};