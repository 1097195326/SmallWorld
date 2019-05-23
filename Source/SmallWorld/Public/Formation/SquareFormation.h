#pragma once
#include "BaseFormation.h"

class SquareFormation : public BaseFormation
{
public:
	SquareFormation();

	virtual void CalculateOffSet(list<ASoldierPawn*> & soldiers) override;


};