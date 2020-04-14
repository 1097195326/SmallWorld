#include "CityActor.h"


ACityActor::ACityActor()
{
	
	//mGeneralGoal = new GeneralGoal();
	//mGeneralGoal->InitWithCityActor(this);

}
void ACityActor::On_Init()
{

}
void ACityActor::On_GameUpdate()
{
	
	//if (mGeneralGoal)
	//{
	//	//mGeneralGoal->Process();
	//}
	for (auto groupManager : mGroupManagers)
	{
		groupManager->On_GameUpdate();
	}

}
void ACityActor::On_Delete()
{
	//mGeneralGoal->End();

	/*delete mGeneralGoal;
	mGeneralGoal = nullptr;*/
}
TSharedPtr<SWidget>	ACityActor::CreateActorDetailWidget()
{
	return SNullWidget::NullWidget;
}