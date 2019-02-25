#pragma once


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
	list<ASoldierPawn*> GetAllSoldier();


	void ChangeFormation(BaseFormation * formation);

};