#pragma once

#include "BaseBuildingActor.h"
#include "BlockDataClass.h"
#include "BlockActor.generated.h"

class ACityActor;



UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()
public:
	ABlockActor();
	virtual void		On_Init() override;
    
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

private:
    
	BlockDataClass * mBlockData;


};
