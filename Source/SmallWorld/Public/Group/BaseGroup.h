#pragma once

#include "SoldierPawn.h"
#include "BaseFormation.h"

#include <list>



class BaseGroup
{
private:
	std::list<ASoldierPawn*> AllSoldier;

public:
	BaseGroup();

	void AddSoldierToGroup(ASoldierPawn * soldier);
	void RemoveSoldierFromGroup(ASoldierPawn * soldier);


	void ChangeFormation(BaseFormation * formation);

};