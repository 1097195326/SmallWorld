#include "RDPakExportModule.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ContentBrowserModule.h"
#include "RDPakExportStyle.h"
#include "RDPakExportCommands.h"
#include "RDGetExportData.h"
#include "RDCookContent.h"
#include "RDCreatePakFile.h"
#include "RDPakWidget.h"
#include "RDPakExportSettings.h"
#include "Http.h"

static const FName PakExportTabName("PakExport");
#define LOCTEXT_NAMESPACE "FRDPakExportModule"
void FRDPakExportModule::StartupModule()
{
	m_bBtnEnabled = true;	
	FRDPakExportStyle::Initialize();
	FRDPakExportStyle::ReloadTextures();
	FRDPakExportCommands::Register();
	m_uiCommands = MakeShareable(new FUICommandList);
	m_uiCommands->MapAction(
		FRDPakExportCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FRDPakExportModule::PluginButtonClicked),
		FCanExecuteAction::CreateRaw(this, &FRDPakExportModule::PluginButtonCanExecute)
		);
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	//Toolbar
	TSharedPtr<FExtender> toolbarExtender = MakeShareable(new FExtender);
	toolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, m_uiCommands, FToolBarExtensionDelegate::CreateRaw(this, &FRDPakExportModule::AddToolbarExtension));
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(toolbarExtender);

	//Menu
	TSharedPtr<FExtender> menuExtender = MakeShareable(new FExtender());
	menuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, m_uiCommands, FMenuExtensionDelegate::CreateRaw(this, &FRDPakExportModule::AddMenuExtension));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(menuExtender);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PakExportTabName, FOnSpawnTab::CreateRaw(this, &FRDPakExportModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPakExportTabTitle", "PakExport"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FContentBrowserModule& contentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	contentBrowserModule.GetOnAssetSelectionChanged().AddLambda([](const TArray<FAssetData>& NewSelectedAssets, bool bIsPrimaryBrowser) {
		URDPakExportSettings::Get()->SetPackagesToExport(NewSelectedAssets);
	});
}

void FRDPakExportModule::ShutdownModule()
{
	FRDPakExportStyle::Shutdown();
	FRDPakExportCommands::Unregister();
}

bool FRDPakExportModule::PluginButtonCanExecute()
{
	return m_bBtnEnabled;
}

void FRDPakExportModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(PakExportTabName);
}

void FRDPakExportModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FRDPakExportCommands::Get().PluginAction);
}

void FRDPakExportModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FRDPakExportCommands::Get().PluginAction);
}

TSharedRef<class SDockTab> FRDPakExportModule::OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPakToolModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PakTool.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SRDPakWidget)
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRDPakExportModule, RDPakExport)