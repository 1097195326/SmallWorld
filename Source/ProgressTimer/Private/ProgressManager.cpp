#include "ProgressManager.h"

ProgressManager * ProgressManager::GetInstance()
{
	static ProgressManager pm;
	return &pm;
}
void ProgressManager::Tick(float delta)
{

}
void ProgressManager::UnRegisterProgress(string inKey)
{
	auto temIter = ProgressCellsMap.find(inKey);
	if (temIter != ProgressCellsMap.end())
	{
		delete temIter->second;
		ProgressCellsMap.erase(temIter);
	}
}