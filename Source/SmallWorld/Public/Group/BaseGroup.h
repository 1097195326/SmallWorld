#pragma once


#include "BaseFormation.h"

#include <list>

using namespace std;


class BaseGroup
{

public:
	BaseGroup();
	virtual ~BaseGroup();

	bool		IsFull();

	virtual void		AddGroupNum();
	virtual void		SubGroupNum();
protected:
	int32		mGroupReadyNum;
	int32		mGroupMaxNum;
	bool		mIsFull;
};