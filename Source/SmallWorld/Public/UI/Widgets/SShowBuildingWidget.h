#pragma once

#include "SBaseCompoundWidget.h"
#include "SBuildingIconItem.h"

class SShowBuildingWidget : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SShowBuildingWidget){}

	SLATE_ARGUMENT(TArray<FString>,IconNames)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:
	TArray<FString>			IconNames;

	TSharedPtr<SGridPanel> IconGridPanel;

};
