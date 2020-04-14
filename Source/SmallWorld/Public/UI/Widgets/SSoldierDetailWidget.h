#pragma once

#include "SGameActorDetailWidget.h"



class SSoldierDetailWidget : public SGameActorDetailWidget
{
public:
	SLATE_BEGIN_ARGS(SSoldierDetailWidget):
		_ActorName(TEXT("")),
		_ActorLevel(TEXT("")),
		_ActorHealth(TEXT("")),
		_DetailWidget()
	{}
	SLATE_ARGUMENT(FString, ActorName)
	SLATE_ARGUMENT(FString, ActorLevel)
	SLATE_ARGUMENT(FString, ActorHealth)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, DetailWidget)

	SLATE_END_ARGS()

		void Construct(const FArguments & InArgs);

protected:




};