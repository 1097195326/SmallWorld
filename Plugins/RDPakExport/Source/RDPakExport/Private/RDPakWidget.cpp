#include "RDPakWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SCheckBox.h"
#include "RDPakExportSettings.h"
#include "PropertyEditorModule.h"
#include "RDGetExportData.h"
#include "RDCreatePakFile.h"

#define FONT_SIZE(a) (FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), a))

SRDPakWidget::SRDPakWidget()
	: m_bHandleing(false)
{
}

void SRDPakWidget::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyEditor = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea, true);
	DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Automatic;
	DetailsViewArgs.bShowOptions = false;
	DetailsViewArgs.ColumnWidth = 0.55f;

	TSharedRef<IDetailsView> DetailsView = PropertyEditor.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(URDPakExportSettings::Get(), true);

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(2, 0, 0, 0)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			.Padding(0.f)
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Right)
				.Padding(0, 20, 20, 0)
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.Padding(0, 0, 10, 0)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SButton)
						.OnClicked_Lambda([]() {
								FString savedPath;
								if (CAssetsSelect::SelectSavePath(savedPath))
								{
									URDPakExportSettings::Get()->SetSavedDir(savedPath);
								}
								return(FReply::Handled());
							})
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("SetSavedDir")))
							.Font(FONT_SIZE(10))
						]
					]

					+ SHorizontalBox::Slot()
					.Padding(0, 0, 0, 0)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SButton)
						.OnClicked_Lambda([]() {
							FPlatformProcess::ExploreFolder(*URDPakExportSettings::Get()->SavedDir);
							return(FReply::Handled());
						})
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("OpenSavedDir")))
							.Font(FONT_SIZE(10))
						]
					]
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.Padding(4, 0, 4, 4)
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					[
						SNew(SVerticalBox)

						+ SVerticalBox::Slot()
						.Padding(0, 10, 0, 0)
						[
							SNew(SBorder)
							.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
							[
								SNew(SVerticalBox)

								+ SVerticalBox::Slot()
								.Padding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.VAlign(VAlign_Center)
									[
										DetailsView->AsShared()
									]
								]
							]
						]
					]
				]

				+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Right)
					.Padding(4, 4, 10, 4)
					[
						SNew(SButton)
						.OnClicked(this, &SRDPakWidget::BtnExport_OnClicked)
						.IsEnabled(this, &SRDPakWidget::BtnExport_Enabled)
						.Text(FText::FromString(TEXT("ExportPak")))
				]
			]
		]
	];
}

FReply SRDPakWidget::BtnExport_OnClicked()
{
	m_bHandleing = true;
	const TArray<FAssetData>& packagesExport = URDPakExportSettings::Get()->GetPackagesToExport();
	FScopedSlowTask SlowTask(packagesExport.Num(), FText::FromString(TEXT("Exporting paks...")));
	SlowTask.MakeDialog(true);
	for (const FAssetData& assetData : packagesExport)
	{
		SlowTask.EnterProgressFrame(1, FText::FromString(FString::Printf(L"Exporting pak %s", *assetData.AssetName.ToString())));
		TArray<FString> filesExport;
		CGetExportData getExportData(assetData);
		getExportData.GetAllFilesExport(filesExport);
		FString pakFilename;
		getExportData.GetDefaultExportFilename(URDPakExportSettings::Get()->SavedDir, pakFilename);

		FString assetsDescriptionStr;
		getExportData.GetAssetDescription(assetsDescriptionStr);

		//cook content
		CCookContent cookContent(filesExport);
		TArray<CCookContent::SCookedInfo> cookedsInf;
		cookContent.Cook(URDPakExportSettings::Get()->GetPlatforms(), cookedsInf);

		//create pak
		for (auto& cookedInf: cookedsInf)
		{
			const FString strCookedPakFilename = FPaths::GetBaseFilename(pakFilename, false) + "_" + cookedInf.TargetPlatform + FPaths::GetExtension(pakFilename, true);
			CCreatePakFile cratePakFile(strCookedPakFilename);
			cratePakFile.CreatePak(cookedInf.FileList, cookedInf.CookedContentDir, assetsDescriptionStr);
		}
	}
	m_bHandleing = false;
	return FReply::Handled();
}

bool SRDPakWidget::BtnExport_Enabled() const
{
	return (URDPakExportSettings::Get()->GetPackagesToExport().Num() > 0) && (!m_bHandleing);
}
