#pragma once
#include "SBaseCompoundWidget.h"

class SArmyCenterContent : public SBaseCompoundWidget
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