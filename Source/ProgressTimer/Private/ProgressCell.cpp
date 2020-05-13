#include "ProgressCell.h"


ProgressCell::ProgressCell(float inTickStep, float inBeginPos, float inEndPos, int inLoopTimes)
	:TickStep(inTickStep),
	BeginPos(inBeginPos),
	EndPos(inEndPos),
	CurrentProcess(inBeginPos),
	fTimer(0.f),
	LoopTimes(inLoopTimes),
	RemainLoopTime(inLoopTimes)
{
    
}
ProgressCell::~ProgressCell()
{
    
}
void ProgressCell::Tick(float delta)
{
	fTimer += delta;
	if (fTimer >= TickStep)
	{
		fTimer -= TickStep;
		CurrentProcess += TickStep;
		bool OneloopIsFinish = CurrentProcess >= EndPos;
		if (CurrentProcess >= EndPos)
		{
			CurrentProcess = EndPos;
		}
		OneloopIsFinish ? --RemainLoopTime : NULL;
		TickFunc(CurrentProcess/EndPos, OneloopIsFinish, RemainLoopTime);
		OneloopIsFinish ? CurrentProcess = BeginPos : NULL;
	}

}