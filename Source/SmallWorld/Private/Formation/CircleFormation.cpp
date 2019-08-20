#include "CircleFormation.h"


CircleFormation::CircleFormation()
{
	mFormationType = CircleFormationType;
}
void CircleFormation::CalculateOffSet(const FormationInfo & _info)
{
	/*list<ASoldierPawn*>::const_iterator iter = soldiers.begin();
	FVector HeaderLocation = (*iter)->GetActorLocation();

	FVector Center;
	int  r = 10;
	int index = 0, row = 0;

	FVector offSet = FVector::ZeroVector;

	for (; iter != soldiers.end(); iter++)
	{
		int R = (r + BuBingOffSet * row);
		int rowCount = (2 * PI * R) / BuBingOffSet;
		if (index >= rowCount)
		{
			row++;
		}
		offSet = FVector(
			FMath::Cos(FMath::DegreesToRadians(360.f / rowCount * index)) * R,
			FMath::Sin(FMath::DegreesToRadians(360.f / rowCount * index)) * R,
			0.f);

		(*iter)->SetFormationPosition(Center + offSet);
	}*/
}