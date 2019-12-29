#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"


class FGameStyle
{
public:

	static void Startup();

	static void Shutdown();

	static  ISlateStyle& Get();

	static FName GetStyleName();
private:
	static TSharedRef<class FSlateStyleSet> Create();

	static TSharedPtr<ISlateStyle> GameStyleInstance;
};