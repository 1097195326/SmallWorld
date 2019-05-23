#pragma once

#include "CoreMinimal.h"
#include "SoldierPawn.h"
#include "GameConfig.h"
#include <list>

enum FormationType
{
	e_CircleFormation,
	e_ConeFormation,
	e_SquareFormation,
	e_HorizonalRectFormation,
	e_VerticalRectFormation,

};

class BaseFormation
{
public:
	BaseFormation();

	virtual void CalculateOffSet(list<ASoldierPawn*> & soldiers) {}

	FormationType GetFormationType();
protected:
	FormationType mFormationType;
	

};