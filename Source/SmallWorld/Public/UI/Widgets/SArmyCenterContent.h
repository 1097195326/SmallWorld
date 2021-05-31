#pragma once
#include "SWrapCompoundWidget.h"

class SArmyCenterContent : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SArmyCenterContent){}

	SLATE_ARGUMENT(class ArmyCenterDataClass * ,ArmyCenter)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);
	virtual void RefreshView() override;

protected:
	class ArmyCenterDataClass * ArmyCenter;

};