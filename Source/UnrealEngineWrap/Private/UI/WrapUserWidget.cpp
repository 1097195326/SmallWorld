//#include "GCore.h"
#include "WrapUserWidget.h"


UWrapUserWidget::UWrapUserWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	//

}

void UWrapUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	On_Init();
}
void UWrapUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	On_Start();
}
void UWrapUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	On_Tick(InDeltaTime);
}
void UWrapUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
	On_Delete();
}
//FReply UWrapUserWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
//{
//	On_FocusReceived();
//	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
//}
//void UWrapUserWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
//{
//	On_FocusLost();
//	Super::NativeOnFocusLost(InFocusEvent);
//}

void UWrapUserWidget::On_Init()
{

}
void UWrapUserWidget::On_Tick(float delta)
{

}
void UWrapUserWidget::On_Delete()
{

}
//void UWrapUserWidget::On_FocusReceived()
//{
//
//}
//void UWrapUserWidget::On_FocusLost()
//{
//
//}
void UWrapUserWidget::SetParentUI(UWrapUserWidget * _ui)
{
	m_ParentUI = _ui;
}