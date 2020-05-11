#pragma once
#include "SBaseCompoundWidget.h"

class SArmyCenterOperationDetail : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SArmyCenterOperationDetail){}

	SLATE_ARGUMENT(class ArmyCenterData * ,ArmyCenter)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);
	virtual void RefreshView() override;

protected:
	class ArmyCenterData * ArmyCenter;

};