#include "RectFormation.h"


RectFormation::RectFormation()
{
	mFormationType = SquareRectFormationType;

}

void RectFormation::CalculateOffSet(const FormationInfo & _info)
{
	BaseFormation::CalculateOffSet(_info);

	float PointX = _info.Offset_X * (_info.Formation_W / 2 + (_info.Formation_W % 2 > 0 ? 1 : 0)) - _info.Offset_X * 0.5f;
	float PointY = _info.Offset_Y * (_info.Formation_L / 2 + (_info.Formation_L % 2 > 0 ? 1 : 0)) - _info.Offset_Y * 0.5f;
	
	int32 index = 1;

	for (int L = 0; L < _info.Formation_L; L++)
	{
		float OffsetY = PointY - L * _info.Offset_Y;

		for (int W = 0; W < _info.Formation_W; W++)
		{
			float OffsetX = PointX - W * _info.Offset_X;
			mFormationLocationMap[index] = FVector(OffsetX,OffsetY,0);
			index++;
		}
	}
}