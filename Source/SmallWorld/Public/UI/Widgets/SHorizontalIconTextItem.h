#pragma once
#include "SBaseCompoundWidget.h"


class SHorizontalIconTextItem : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHorizontalIconTextItem):
		_InImageWidth(64),
		_InImageHeight(64)
	{}

	SLATE_ARGUMENT(const FSlateBrush*, InImageBrush)
		SLATE_ARGUMENT(int32, InImageWidth)
		SLATE_ARGUMENT(int32, InImageHeight)
		SLATE_ATTRIBUTE(FString, InShowText)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
protected:
	//TAttribute<FSlateBrush*> ImageBrush;
	const FSlateBrush* ImageBrush;
	TAttribute<FString> ShowText;

};