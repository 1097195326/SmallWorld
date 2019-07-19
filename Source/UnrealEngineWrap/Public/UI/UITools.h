#pragma once

#include "GObject.h"
#include "ButtonScript.h"
#include "CoreMinimal.h"
#include "BaseUI.h"
#include <list>


#define UI_T UITools::GetInstance()

class UNREALENGINEWRAP_API UITools : public GObject
{
private:
    // single instance
    TMap<UButton*, UButtonScript*>        m_ButtonMap;

public:
    static UITools * GetInstance();

    UBaseUI* OpenUI(const FString & _uiName,UBaseUI * _ParentUI = nullptr);

	void	TopHintText(const FString & hintText, float showSecond = 2);


    template<typename T>
    void RegisterButton(int _bid, UButton * _btn, T * _obj, void(T::*_func)(int))
    {
		UButtonScript * bs = UButtonScript::Create();
		bs->BindFunctionCall(_bid, _btn, _obj, _func);
		m_ButtonMap.Add(_btn, bs);
    }
	template<typename T>
	void RegisterButton(int _bid, UButton * _btn, T * _obj, void(T::*_func)(int,ButtonAction),ButtonAction _action)
	{
		UButtonScript * bs = UButtonScript::Create();
		bs->BindFunctionCall(_bid, _btn, _obj, _func,_action);
		m_ButtonMap.Add(_btn, bs);
	}
    void UnRegisterButton(UButton * _btn);

};
