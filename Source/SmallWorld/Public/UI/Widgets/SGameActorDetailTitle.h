#pragma once

#include "SBaseCompoundWidget.h"



class SGameActorDetailTitle : public SBaseCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorDetailTitle):
		_ActorName(TEXT("")),
		_ActorLevel(TEXT("")),
		_ActorHealth(TEXT(""))
	{}
	SLATE_ARGUMENT(FString, ActorName)
	SLATE_ARGUMENT(FString, ActorLevel)
	SLATE_ARGUMENT(FString, ActorHealth)

	SLATE_END_ARGS()

	void Construct(const FArguments & InArgs);

protected:




};