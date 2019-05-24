#pragma once
#include "BaseFormation.h"

class SquareFormation : public BaseFormation
{
public:
	SquareFormation();

	virtual void CalculateOffSet(const FormationInfo & _info) override;


};