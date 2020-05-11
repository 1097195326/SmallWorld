#pragma once

#include "SCompoundWidget.h"
#include "SlateCore.h"
#include "ButtonRegister.h"


class SBaseCompoundWidget : public SCompoundWidget
{
public:
	virtual void RefreshView(){}

	void	SetGameData(void * InData) { GameData = InData; }
	template<typename T>
	T *	GetGameData() { return dynamic_cast<T*>(GameData); }
protected:
	void *  GameData;
};