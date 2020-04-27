#pragma once
#include "SBaseCompoundWidget.h"


class SHorizontalIconTextItem : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHorizontalIconTextItem){}

	SLATE_ATTRIBUTE(FSlateBrush *, InImageBrush)
	SLATE_ATTRIBUTE(FString , InShowText)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
protected:
	TAttribute<FSlateBrush *> ImageBrush;
	TAttribute<FString> ShowText;

};