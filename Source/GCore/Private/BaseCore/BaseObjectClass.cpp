#include "BaseObjectClass.h"


BaseObjectClass::BaseObjectClass()
{
	ObjectId = FGuid::NewGuid();

}
BaseObjectClass::~BaseObjectClass()
{

}
FGuid BaseObjectClass::GetObjectId()
{
	return ObjectId;
}