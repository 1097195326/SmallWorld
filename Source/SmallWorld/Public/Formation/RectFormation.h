#pragma once
#include "BaseFormation.h"

class RectFormation : public BaseFormation
{
public:
	RectFormation();

	virtual void CalculateOffSet(const FormationInfo & _info) override;


};