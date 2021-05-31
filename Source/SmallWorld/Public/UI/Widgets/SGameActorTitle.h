#pragma once

#include "SWrapCompoundWidget.h"



class SGameActorTitle : public SWrapCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameActorTitle):
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