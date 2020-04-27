#pragma once
#include "SBaseCompoundWidget.h"

class SHorizontalItemOperation: public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHorizontalItemOperation){}

	SLATE_ATTRIBUTE(FText,InShowText)
	SLATE_ATTRIBUTE(FString,InButtonText)
	//SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	void OnValueChange(float InValue);

	TAttribute<FText> ShowText;
	TAttribute<FString> ButtonShowText;


};