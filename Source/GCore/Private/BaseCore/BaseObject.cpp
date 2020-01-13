#include "BaseObject.h"


BaseObject::BaseObject()
{
	m_ID = FGuid::NewGuid();

}
BaseObject::~BaseObject()
{

}
FGuid BaseObject::GetID()
{
	return m_ID;
}