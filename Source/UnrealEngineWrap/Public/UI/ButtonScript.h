#pragma once

#include "GameObjectClass.h"
#include "CoreMinimal.h"
#include "UMG/Public/Components/Button.h"
#include "Slate/Public/Widgets/Input/SButton.h"
#include <functional>
#include "ButtonScript.generated.h"

enum ButtonAction
{
	B_Click,
	B_Pressed,
	B_Released,
};

UCLASS()
class UNREALENGINEWRAP_API UButtonScript : public UObject//, public GameObjectClass
{
	GENERATED_BODY()
	
private:
	typedef std::function<void(int32)> BUTTON_CLICK_CALL;

	int		m_Index;
	BUTTON_CLICK_CALL	m_Call;
public:
	static UButtonScript * Create();
	
	UFUNCTION()
		void OnUButtonClick();

	FReply  OnSButtonClick();

	template<typename T>
	void BindFunctionCall(int _index,UButton * _btn, T* _obj, void(T::*_func)(int32))
	{
		m_Index = _index;
		_btn->OnClicked.AddDynamic(this, &UButtonScript::OnUButtonClick);
		m_Call = BUTTON_CLICK_CALL(std::bind(_func,_obj,std::placeholders::_1));
	}
	template<typename T>
	void BindFunctionCall(int _index, SButton * _btn, T* _obj, void(T::*_func)(int32))
	{
		m_Index = _index;
		_btn->SetOnClicked(FOnClicked::CreateUObject(this, &UButtonScript::OnSButtonClick));
		m_Call = BUTTON_CLICK_CALL(std::bind(_func, _obj, std::placeholders::_1));
	}
};
