#pragma once

#include "SBaseCompoundWidget.h"
#include "SBuildingIconItem.h"

class SShowBuildingWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SShowBuildingWidget){}

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

};
