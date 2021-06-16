#pragma once

#include "SWrapCompoundWidget.h"


class STextButton : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STextButton) {}
	
	SLATE_ARGUMENT(float, Width)
	SLATE_ARGUMENT(float, Height)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);
	~STextButton();
protected:


};