#include "BaseObject.h"


BaseObject::BaseObject()
{
	FPlatformMisc::CreateGuid(m_ID);

}
BaseObject::~BaseObject()
{

}
FGuid BaseObject::GetID()
{
	return m_ID;
}