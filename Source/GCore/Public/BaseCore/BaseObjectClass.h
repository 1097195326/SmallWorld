#pragma once



#include "CoreMinimal.h"
#include "ClassReflect.h"
#include <utility>

class GCORE_API BaseObjectClass
{

protected:
	FGuid	ObjectId;
public:
	BaseObjectClass();
	virtual ~BaseObjectClass();

public:

	FGuid GetObjectId();

};

