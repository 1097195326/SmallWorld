#include "BaseFormation.h"


BaseFormation::BaseFormation()
{

}
FormationType BaseFormation::GetFormationType()
{
	return mFormationType;
}
void BaseFormation::SetFormationType(FormationType _type)
{
	mFormationType = _type;
}
FVector BaseFormation::GetLocationByIndex(int _index)
{
	return mFormationLocationMap[_index];
}