#include "SSoldierDetailWidget.h"


void SSoldierDetailWidget::Construct(const FArguments & InArgs)
{

	SGameActorDetailWidget::Construct(SGameActorDetailWidget::FArguments()
		.ActorName(InArgs._ActorName)
		.ActorLevel(InArgs._ActorLevel)
		.ActorHealth(InArgs._ActorHealth)
		.DetailWidget(InArgs._DetailWidget));
	

}