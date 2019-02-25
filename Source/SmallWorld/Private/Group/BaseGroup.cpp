#include "BaseGroup.h"

BaseGroup::BaseGroup()
{

}
void BaseGroup::AddSoldierToGroup(ASoldierPawn * soldier)
{
	AllSoldier.push_back(soldier);
}
void BaseGroup::RemoveSoldierFromGroup(ASoldierPawn * soldier)
{
	AllSoldier.remove(soldier);
}
list<ASoldierPawn*> BaseGroup::GetAllSoldier()
{
	return AllSoldier;
}