#pragma once
#include "BaseFormation.h"

class VerticalRectFormation : public BaseFormation
{
public:
	VerticalRectFormation();


	virtual void CalculateOffSet(const FormationInfo & _info) override;

};