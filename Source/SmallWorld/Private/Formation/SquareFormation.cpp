#include "SquareFormation.h"


SquareFormation::SquareFormation()
{
	mFormationType = e_SquareFormation;

}

void SquareFormation::CalculateOffSet(list<ASoldierPawn *> & soldiers)
{
	list<ASoldierPawn*>::const_iterator iter = soldiers.begin();
	FVector HeaderLocation = (*iter)->GetActorLocation();
	FVector ForwardVector = (*iter)->GetActorForwardVector();
	FVector RightVector = (*iter)->GetActorRightVector();

	int index = 0;
	int row = 0;
	FVector LeftVec = FVector::ZeroVector, RightVec = FVector::ZeroVector, RowVec = FVector::ZeroVector;

	for (; iter != soldiers.end(); iter++)
	{
		ASoldierPawn * Soldier = (*iter);
		if (index % 9 == 0)
		{

			LeftVec = -RightVector;
			RightVec = RightVector;
			RowVec = ForwardVector * -BuBingOffSet * row;
			Soldier->SetFormationPosition(HeaderLocation + LeftVec + RowVec);
			Soldier->SetOffsetToLeader(LeftVec + RowVec);
			row++;
		}
		else
		{
			if (index % 2 == 0)
			{
				LeftVec = LeftVec - RightVector * BuBingOffSet;
				Soldier->SetFormationPosition(HeaderLocation + LeftVec + RowVec);
				Soldier->SetOffsetToLeader(LeftVec + RowVec);
			}
			else
			{
				RightVec = RightVec + RightVector * BuBingOffSet;
				Soldier->SetFormationPosition(HeaderLocation + RightVec + RowVec);
				Soldier->SetOffsetToLeader(RightVec + RowVec);
			}
		}

		index++;
	}
}