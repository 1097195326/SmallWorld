#pragma once


#include "BaseFormation.h"

#include <list>

using namespace std;


class BaseGroup
{
private:
	std::list<ASoldierPawn*> AllSoldier;
	BaseFormation * CurrrentFormation;
public:
	BaseGroup();

	void AddSoldierToGroup(ASoldierPawn * soldier);
	void RemoveSoldierFromGroup(ASoldierPawn * soldier);
	list<ASoldierPawn*> GetAllSoldier();


	void ChangeFormation(BaseFormation * formation);

};