#pragma once

#include "BaseFormation.h"

class ConeFormation : public BaseFormation
{
public:
	ConeFormation();

	virtual void CalculateOffSet(const FormationInfo & _info) override;


};