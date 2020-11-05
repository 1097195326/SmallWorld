#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Misc/MonitoredProcess.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SRDPakWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SRDPakWidget) {}

	SLATE_END_ARGS()

public:
	SRDPakWidget();
	void Construct(const FArguments& InArgs);
	FReply BtnExport_OnClicked();
	bool BtnExport_Enabled() const;

private:
	bool m_bHandleing;
};