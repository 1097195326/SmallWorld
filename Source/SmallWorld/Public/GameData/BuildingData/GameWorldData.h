#pragma once

#include "HordeData.h"


class GameWorldData : public DataR
{
protected:
    
public:
	GameWorldData();
    ~GameWorldData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    

	// Manage HordeId
	
	bool	HordeIdIsValid(FGuid hordeId);
	bool	DestroyHordeId(FGuid hordeId);
private:


	TArray<FGuid>  HordeList;

    
};
