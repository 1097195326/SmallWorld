#pragma once

#include "BaseFormation.h"

class CircleFormation : public BaseFormation
{
public:
	CircleFormation();

	virtual void CalculateOffSet(list<ASoldierPawn*> & soldiers) override;

};