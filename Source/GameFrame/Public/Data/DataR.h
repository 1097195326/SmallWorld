#pragma once
#include "GData.h"

class GAMEFRAME_API DataR : public GData
{
protected:
	int		m_Tid;
	int		m_Rid;

public:
	int GetTid();
	int GetRid();



};