#include "BaseFormation.h"


BaseFormation::BaseFormation()
{

}
FormationType BaseFormation::GetFormationType()
{
	return mFormationType;
}
FVector BaseFormation::GetLocationByIndex(int _index)
{
	return mFormationLocationMap[_index];
}