#pragma once



#include "CoreMinimal.h"
#include "ClassReflect.h"
#include <utility>

class GCORE_API BaseObject
{

private:
	FGuid	m_ID;
public:
	BaseObject();
	virtual ~BaseObject();

public:

	FGuid GetID();

};

