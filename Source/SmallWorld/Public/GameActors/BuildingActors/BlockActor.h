#pragma once

#include "BaseBuildingActor.h"
#include "BlockData.h"
#include "BlockActor.generated.h"

class ACityActor;



UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()
public:
	ABlockActor();
	virtual void		On_Init() override;
    
private:
    
	BlockData * mBlockData;


};
