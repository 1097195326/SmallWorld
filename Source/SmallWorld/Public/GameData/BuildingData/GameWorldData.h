#pragma once
#include "BaseBuildingData.h"


class GameWorldData : public DataR
{
protected:
    
public:
	GameWorldData();
    ~GameWorldData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    

	// Manage HordeId
	int32	CreateHordeId();
	bool	HordeIdIsValid(int32 hordeId);
	bool	DestroyHordeId(int32 hordeId);
private:

	TArray<int32>  HordeList;

    
};
