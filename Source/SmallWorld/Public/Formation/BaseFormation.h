#pragma once

#include "CoreMinimal.h"
#include "SoldierPawn.h"
#include "GameConfig.h"
#include "GObject.h"
#include <list>




enum FormationType
{
	e_CircleFormation,
	e_ConeFormation,
	e_SquareRectFormation,
	e_HorizonalRectFormation,
	e_VerticalRectFormation,

};
struct FormationInfo
{
	float Offset_X;
	float Offset_Y;
	int32 Formation_W;
	int32 Formation_L;
};

class BaseFormation : public GObject
{
public:
	BaseFormation();

	virtual void		CalculateOffSet(const FormationInfo & _info) {}

	FVector				GetLocationByIndex(int _index);
	FormationType		GetFormationType();
protected:
	FormationType		mFormationType;
	
	map<int, FVector>	mFormationLocationMap;

};