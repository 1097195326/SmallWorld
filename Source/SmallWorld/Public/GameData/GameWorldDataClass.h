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
	void	InitUserData(class UserDataClass * InUserData);
	void	SetUserDataRace(class UserDataClass * InUserData,RaceEnum InRace);

	// Manage HordeId
	HordeDataClass * CreateHordeData(RaceEnum InRace = Race_None);
	HordeDataClass *	GetHordeDataById(const FGuid & InHordeId);
	TArray<HordeDataClass*>	GetHordeDatByRace(RaceEnum InRace);

	bool	HordeIdIsValid(const FGuid & InHordeId);
	bool	DestroyHordeId(const FGuid & InHordeId);
private:
	TMap<FGuid,HordeDataClass *>	HordeDataMap;


    
};
