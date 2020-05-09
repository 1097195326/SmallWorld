#include "ProgressManager.h"

ProgressManager * ProgressManager::GetInstance()
{
	static ProgressManager pm;
	return &pm;
}
void ProgressManager::Tick(float delta)
{
	FinishedVector.clear();
	FinishedVector.resize(ProgressCellsMap.size());
	for (auto temIter : ProgressCellsMap)
	{
		ProgressCell & temCell = temIter.second; 
		temCell.Tick(delta);
		if (temCell.IsFinished())
		{
			FinishedVector.push_back(temIter.first);
		}
	}
	for (auto temKey : FinishedVector)
	{
		ProgressCellsMap.erase(temKey);
	}


}
void ProgressManager::UnRegisterProgress(string inKey)
{
	auto temIter = ProgressCellsMap.find(inKey);
	if (temIter != ProgressCellsMap.end())
	{
		ProgressCellsMap.erase(temIter);
	}
}