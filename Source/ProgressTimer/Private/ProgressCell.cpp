#include "ProgressCell.h"


ProgressCell::ProgressCell(float inTickStep, float inBeginPos, float inEndPos, int inLoopTimes)
	:TickStep(inTickStep),
	BeginPos(inBeginPos),
	EndPos(inEndPos),
	CurrentProcess(0.f),
	LoopTimes(inLoopTimes),
	RemainLoopTime(inLoopTimes)
{
    
}
ProgressCell::~ProgressCell()
{
    
}