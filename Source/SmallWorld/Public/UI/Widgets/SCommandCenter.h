#pragma once

#include "SBaseCompoundWidget.h"

class SCommandCenter : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCommandCenter) {}

	SLATE_ARGUMENT(class CommandCenterDataClass *, CommandCenterData)

		SLATE_END_ARGS()

		void Construct(const FArguments & InArgs);
	virtual void RefreshView() override;

protected:
	FReply OnButtonClicked(int32 InIndex);

	class CommandCenterDataClass * CommandCenterData;

};