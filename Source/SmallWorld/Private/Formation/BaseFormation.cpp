#include "BaseFormation.h"


BaseFormation::BaseFormation()
{

}
FormationSpace::FormationType BaseFormation::GetFormationType()
{
	return mFormationType;
}
void BaseFormation::CalculateOffSet(const FormationInfo & _info)
{
	mFormationInfo = _info;
}
void BaseFormation::SetFormationType(FormationType _type)
{
	mFormationType = _type;
}
FVector BaseFormation::GetLocationByIndex(int _index)
{
	return mFormationLocationMap[_index];
}