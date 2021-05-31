#pragma once

#include "GameObjectClass.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"  
#include "Runtime/UMG/Public/UMGStyle.h"  
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"  
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "WrapUserWidget.generated.h"

UCLASS()
class UNREALENGINEWRAP_API UWrapUserWidget : public UUserWidget, public GameObjectClass
{
	GENERATED_UCLASS_BODY()

public:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	/*virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;*/

public:
	void SetParentUI(UWrapUserWidget * _ui);
	virtual void On_Init() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	/*virtual void On_FocusReceived();
	virtual void On_FocusLost();*/
protected:
	UWrapUserWidget * m_ParentUI;

};