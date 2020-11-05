#pragma once
#include "Modules/ModuleManager.h"


// DECLARE_LOG_CATEGORY_EXTERN(PAKLog, Log, All);
class FToolBarBuilder;
class FRDPakExportModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	bool PluginButtonCanExecute();
	
private:
	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> m_uiCommands;
	bool m_bBtnEnabled;
};
