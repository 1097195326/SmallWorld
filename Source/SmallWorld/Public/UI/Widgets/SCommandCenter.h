#pragma once

#include "SWrapCompoundWidget.h"

class SCommandCenter : public SWrapCompoundWidget
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