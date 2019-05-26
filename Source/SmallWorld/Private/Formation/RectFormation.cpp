#include "RectFormation.h"


RectFormation::RectFormation()
{
	mFormationType = e_SquareRectFormation;

}

void RectFormation::CalculateOffSet(const FormationInfo & _info)
{

	FVector StartPoint = FVector(
		_info.Offset_X * (_info.Formation_W / 2 + _info.Formation_W % 2 > 0 ? 1 : 0),
		_info.Offset_Y * (_info.Formation_L / 2 + _info.Formation_L % 2 > 0 ? 1 : 0),
		0);
	int32 index = 0;

	for (int L = 0; L < _info.Formation_L; L++)
	{
		float OffsetY = StartPoint.Y - L * _info.Offset_Y;

		for (int W = 0; W < _info.Formation_W; W++)
		{
			float OffsetX = StartPoint.X - W * _info.Offset_X;
			mFormationLocationMap[index] = FVector(OffsetX,OffsetY,0);
		}
	}
}