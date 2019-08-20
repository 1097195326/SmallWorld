#pragma once

#include "CoreMinimal.h"
#include "SoldierPawn.h"
#include "GameConfig.h"
#include "GObject.h"
#include <list>



namespace FormationSpace
{
	enum FormationType
	{
		CircleFormationType,
		ConeFormationType,
		SquareRectFormationType,
		HorizonalRectFormationType,
		VerticalRectFormationType,

	};
	struct FormationInfo
	{
		float Offset_X;
		float Offset_Y;
		int32 Formation_W;
		int32 Formation_L;
	};
};

using namespace FormationSpace;


class BaseFormation : public GObject
{
public:
	BaseFormation();

	virtual void		CalculateOffSet(const FormationInfo & _info) {}

	FVector				GetLocationByIndex(int _index);

	void				SetFormationType(FormationType _type);
	FormationType		GetFormationType();
protected:
	FormationType		mFormationType;
	
	map<int, FVector>	mFormationLocationMap;

};