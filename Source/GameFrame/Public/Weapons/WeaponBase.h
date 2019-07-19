#pragma once

#include "GObject.h"

class PawnBase;


class WeaponBase : public GObject
{
public:
	WeaponBase();
	~WeaponBase();

	virtual void		AttackEnemy();

	void				SetOwner(PawnBase * temOwner);
	PawnBase *			GetOwner();
	
	template<typename T>
	T* GetOwner()
	{
		return Cast<T*>(Owner);
	}
	
protected:

	PawnBase * Owner;

};