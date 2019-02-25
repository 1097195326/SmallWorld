#include "VerticalRectFormation.h"



VerticalRectFormation::VerticalRectFormation()
{
	mFormationType = e_VerticalRectFormation;

}
void VerticalRectFormation::CalculateOffSet(const list<ASoldierPawn*> & soldiers)
{
	int Num = soldiers.size();
	list<ASoldierPawn*>::const_iterator iter = soldiers.begin();
	bool IsEven = Num % 2 > 0 ? false : true;
	for (int i = 0; i < Num; ++i)
	{

	}
}