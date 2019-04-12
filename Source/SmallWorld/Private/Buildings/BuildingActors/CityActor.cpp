#include "CityActor.h"


ACityActor::ACityActor()
{
	BlockMap.reserve(11);
	CitySize = 11;

	for (int x = 0; x < CitySize; x++)
	{
		for (int y = 0; y < CitySize; y++)
		{
			/*UGameplayStatics::BeginDeferredActorSpawnFromClass(this,ABlockActor::StaticClass(),)

			BlockMap[x][y] = Cast<ABlockActor>(GetWorld()->SpawnActor<ABlockActor>());*/

		}
	}

}
void ACityActor::InitData(CityData * _data)
{
	mData = _data;


}