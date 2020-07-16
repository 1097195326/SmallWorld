#pragma once

#include "SingleTemplateClass.h"
#include "ButtonScript.h"
#include "CoreMinimal.h"
#include "BaseUI.h"
#include <list>



class UNREALENGINEWRAP_API ButtonRegister : public SingleTemplateClass<ButtonRegister>
{
private:
    // single instance
	TMap<UButton*, TArray<UButtonScript*>>        m_UButtonMap;
	TMap<SButton*, TArray<UButtonScript*>>        m_SButtonMap;

public:

    template<typename T>
    void RegisterButton(UButton * _btn, T * _obj, void(T::*_func)(int32), int32 _bid = 0)
    {
		UButtonScript * bs = UButtonScript::Create();
		bs->BindFunctionCall(_bid, _btn, _obj, _func);
		if (m_UButtonMap.Contains(_btn))
		{
			m_UButtonMap[_btn].Add(bs);
		}
		else
		{
			m_UButtonMap.Add(_btn, { bs });
		}
    }
	template<typename T>
	void RegisterButton(SButton * _btn, T * _obj, void(T::*_func)(int32), int _bid = 0)
	{
		UButtonScript * bs = UButtonScript::Create();
		bs->BindFunctionCall(_bid, _btn, _obj, _func);
		if (m_SButtonMap.Contains(_btn))
		{
			m_SButtonMap[_btn].Add(bs);
		}
		else
		{
			m_SButtonMap.Add(_btn, { bs });
		}
	}
	void UnRegisterButton(UButton * _btn);
	void UnRegisterButton(SButton * _btn);

};
