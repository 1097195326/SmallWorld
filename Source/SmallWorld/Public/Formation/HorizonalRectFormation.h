#pragma once
#include "BaseFormation.h"

class HorizonalRectFormation : public BaseFormation
{
public:
	HorizonalRectFormation();

	virtual void CalculateOffSet(list<ASoldierPawn*> & soldiers) override;


};