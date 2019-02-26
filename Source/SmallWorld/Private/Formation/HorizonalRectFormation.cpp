#include "HorizonalRectFormation.h"


HorizonalRectFormation::HorizonalRectFormation()
{
	mFormationType = e_HorizonalRectFormation;
}

void HorizonalRectFormation::CalculateOffSet(const list<ASoldierPawn *> & soldiers)
{
	list<ASoldierPawn*>::const_iterator iter = soldiers.begin();
	FVector HeaderLocation = (*iter)->GetActorLocation();

	iter++;
	int index = 0;
	int row = 0;
	FVector LeftVec = FVector::ZeroVector, RightVec = FVector::ZeroVector, RowVec = FVector::ZeroVector;

	for (; iter != soldiers.end(); iter++)
	{
		if (index % 9 == 0)
		{
			row++;
			LeftVec = FVector(-BuBingOffSet * 0.5f, 0.f, 0.f);
			RightVec = FVector(BuBingOffSet * 0.5f, 0.f, 0.f);
			RowVec = FVector(0.f, -BuBingOffSet * row, 0.f);
			(*iter)->SetFormationPosition(HeaderLocation + LeftVec + RowVec);
			(*iter)->SetOffsetToLeader(LeftVec + RowVec);
		}
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
			(*iter)->SetOffsetToLeader(RightVec + RowVec);
		}
		index++;
	}
}