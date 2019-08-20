#include "ConeFormation.h"


ConeFormation::ConeFormation()
{
	mFormationType = ConeFormationType;
}
void ConeFormation::CalculateOffSet(const FormationInfo & _info)
{
	/*list<ASoldierPawn*>::const_iterator iter = soldiers.begin();
	FVector HeaderLocation = (*iter)->GetActorLocation();

	int index = 0;
	int row = 0;
	int ConeIndex = 1;
	FVector LeftVec = FVector::ZeroVector, RightVec = FVector::ZeroVector, RowVec = FVector::ZeroVector;

	for (; iter != soldiers.end(); iter++)
	{
		if (index % ConeIndex == 0)
		{
			if (ConeIndex <= 9)
			{
				ConeIndex += 2;
			}
			row++;
			LeftVec = FVector(0.f, 0.f, 0.f);
			RightVec = FVector(0.f, 0.f, 0.f);
			RowVec = FVector(0.f, -BuBingOffSet * row, 0.f);
			(*iter)->SetFormationPosition(HeaderLocation + LeftVec + RowVec);
			(*iter)->SetFormationPosition(LeftVec + RowVec);
		}
		else
		{
			if (index % 2 == 0)
			{
				LeftVec = LeftVec + FVector(-BuBingOffSet, 0.f, 0.f);
				(*iter)->SetFormationPosition(HeaderLocation + LeftVec + RowVec);
				(*iter)->SetOffsetToLeader(LeftVec + RowVec);
			}
			else
			{
				RightVec = RightVec + FVector(BuBingOffSet, 0.f, 0.f);
				(*iter)->SetFormationPosition(HeaderLocation + RightVec + RowVec);
				(*iter)->SetFormationPosition(RightVec + RowVec);
			}
		}
		index++;
		
	}*/
}