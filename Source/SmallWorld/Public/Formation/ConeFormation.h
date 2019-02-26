#pragma once

#include "BaseFormation.h"

class ConeFormation : public BaseFormation
{
public:
	ConeFormation();

	virtual void CalculateOffSet(const list<ASoldierPawn*> & soldiers) override;


};