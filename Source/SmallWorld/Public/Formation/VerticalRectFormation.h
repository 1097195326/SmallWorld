#pragma once
#include "BaseFormation.h"

class VerticalRectFormation : public BaseFormation
{
public:
	VerticalRectFormation();


	virtual void CalculateOffSet(list<ASoldierPawn*> & soldiers) override;

};