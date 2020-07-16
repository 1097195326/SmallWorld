#pragma once

#include "HordeDataClass.h"



class GameWorldDataClass : public RuntimeDataClass
{
protected:
    
public:
	GameWorldDataClass();
    ~GameWorldDataClass();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    
	void	InitWorldData();
	void	InitUserData(class UserDataClass * userData);
	// Manage HordeId
	HordeDataClass * CreateHordeData();
	HordeDataClass *	GetHordeDataById(FGuid hordeId);

	bool	HordeIdIsValid(FGuid hordeId);
	bool	DestroyHordeId(FGuid hordeId);
private:
	TMap<FGuid,HordeDataClass *>	HordeDataMap;


    
};
