#pragma once

#include "CoreMinimal.h"
#include "SoldierPawn.h"
#include "GameConfig.h"
#include "GameObjectClass.h"
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


class BaseFormation : public GameObjectClass
{
public:
	BaseFormation();

	virtual void			CalculateOffSet(const FormationInfo & _info);

	FVector					GetLocationByIndex(int _index);

	void					SetFormationType(FormationType _type);
	FormationType			GetFormationType();
	inline const  FormationInfo& 	GetFormationInfo() { return mFormationInfo; }
protected:
	FormationType		mFormationType;
	FormationInfo		mFormationInfo;

	map<int, FVector>	mFormationLocationMap;

};