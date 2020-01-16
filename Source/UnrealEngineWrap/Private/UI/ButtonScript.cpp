//#include "GCore.h"
#include "ButtonScript.h"


UButtonScript * UButtonScript::Create()
{
	UButtonScript * bs = NewObject<UButtonScript>();
	bs->AddToRoot();
	return bs;
}
void UButtonScript::OnUButtonClick()
{
	m_Call(m_Index);
}
FReply UButtonScript::OnSButtonClick()
{
	m_Call(m_Index);
	return FReply::Handled();
}