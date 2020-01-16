#include "ButtonRegister.h"


void ButtonRegister::UnRegisterButton(UButton * _btn)
{
	while (m_UButtonMap.Contains(_btn))
	{
		TArray<UButtonScript *> bsArray = m_UButtonMap[_btn];
		for (auto bs : bsArray)
		{
			bs->RemoveFromRoot();
		}
		m_UButtonMap.Remove(_btn);
	}
}
void ButtonRegister::UnRegisterButton(SButton * _btn)
{
	while (m_SButtonMap.Contains(_btn))
	{
		TArray<UButtonScript *> bsArray = m_SButtonMap[_btn];
		for (auto bs : bsArray)
		{
			bs->RemoveFromRoot();
		}
		m_SButtonMap.Remove(_btn);
	}
}