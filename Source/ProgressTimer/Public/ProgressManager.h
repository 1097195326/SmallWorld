#pragma once

#include <map>

#include "ProgressCell.h"


class PROGRESSTIMER_API ProgressManager
{
public:
	static ProgressManager * GetInstance();

	void	Tick(float delta);

	template<typename T>
	void RegisterProgress(string InKey,int loopTimes, float tickStep,float beginPos,float endPos, T * _obj, void(T::*_func)(float, bool, int))
	{
		auto temIter = ProgressCellsMap.find(InKey)
		if (temIter == ProgressCellsMap.end())
		{
			ProgressCell* TemCell = new ProgressCell(tickStep,beginPos,endPos,loopTimes);
			TemCell->RegisterHeader(_obj, _func);
			ProgressCellsMap.insert(std::pair<string, ProgressCell*>(InKey, TemCell));
		}
		else
		{

		}

	}
	void UnRegisterProgress(string inKey);

private:
	map<string, ProgressCell*>  ProgressCellsMap;


};
