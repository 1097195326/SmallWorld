#pragma once
#include "BaseBuildingData.h"


class HouseData : public BaseBuildingData
{
protected:
    
public:
	HouseData();
    ~HouseData();
    
    
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;
    

	void	ChangePeopleNum(int32 plusNum);
	inline int32	GetPeopleNum() { return PeopleNum; }
protected:
	int32	PeopleNum;
    
};
