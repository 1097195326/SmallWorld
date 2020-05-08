#pragma once


#include <functional>
#include <string>

using namespace std;

class PROGRESSTIMER_API ProgressCell
{
public:
	typedef function<void(float InProgress, bool InIsFinish,int LoopTimes)> TickCallBackFunc;
	TickCallBackFunc TickFunc;

	ProgressCell(float inTickStep, float inBeginPos, float inEndPos, int inLoopTimes);
    virtual ~ProgressCell();
    
    template<typename T>
    void RegisterHeader(T * _obj, void(T::*_func)(float,bool,int))
    {
		TickFunc = bind(_func, _obj, placeholders::_1, placeholders::_2, placeholders::_3);
        
	}
	void	Tick(float delta);
	inline bool	IsFinished() const { return RemainLoopTime == 0; }
protected:
	float TickStep;
	float BeginPos;
	float EndPos;
	float CurrentProcess;
	int LoopTimes;
	int RemainLoopTime;

};
