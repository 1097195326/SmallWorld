#include "MainViewUIController.h"
#include "SHordePowerWidget.h"
#include "SBuildingIconItemListWidget.h"
#include "GameDataManager.h"
#include "SServiceDragDropWidget.h"
#include "SmallWorldInstance.h"
#include "UserController.h"
#include "UserViewportClient.h"
#include "GameMenuWidgetStyle.h"
#include "SGameMenuPageWidget.h"

MainViewUIController::MainViewUIController()
{
	RaceMenuPage = MakeShareable(new FGameMenuPage());
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Human")),this,&MainViewUIController::MenuOperation,1);
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Orc")), this, &MainViewUIController::MenuOperation,2);
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Elf")), this, &MainViewUIController::MenuOperation,3);
	RaceMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race_Undead")), this, &MainViewUIController::MenuOperation,4);

	MainMenuPage = MakeShareable(new FGameMenuPage());
	MainMenuPage->MenuTitle = FText::FromString(TransLanguage("Game_Race"));
	RaceMenuItem = MainMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Race")), RaceMenuPage);
	MainMenuPage->AddMenuItem(FText::FromString(TransLanguage("Game_Start")), this, &MainViewUIController::MenuOperation,5);


}
void MainViewUIController::MenuOperation(int32 InIndex)
{
	switch (InIndex)
	{
	case 1:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Human"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}	
	case 2:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Orc"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 3:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Elf"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 4:
	{
		RaceMenuItem->Text = FText::FromString(TransLanguage("Game_Race_Undead"));
		MainMenuPage->RootMenuPageWidget->MenuGoBack();
		break;
	}
	case 5:
		break;
	}
}
void MainViewUIController::InitControllerView()
{
	ControllerView->AddSlot(0)
		[
			SNew(SServiceDragDropWidget)
		];
	

}
void MainViewUIController::OnEnter()
{
	MainMenuPage->InitialiseRootMenu(User_Controller, FGameStyle::Get().GetWidgetStyle<FGameMenuStyle>("Menu_MainView"), User_GameClient);
	
	MainMenuPage->ShowRootMenu();

}
void MainViewUIController::OnExit()
{
	MainMenuPage->DestroyRootMenu();
}
void MainViewUIController::SelectGameActor(AGameActor * GameActorPtr)
{
	CheckNullPtr(GameActorPtr);
	MiddleBottomSlot->AttachWidget(GameActorPtr->CreateActorDetailWidget().ToSharedRef());
	
}
void MainViewUIController::SelectHorde()
{

}

//// -----------------
//TSharedPtr<SWidget>	MainViewUIController::TestWidget()
//{
//	TSharedPtr<SImage> ShowImage = SNew(SImage);
//	FString  PackageName = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl0");
//	FString PackageFilename;
//	if (FPackageName::DoesPackageExist(PackageName, NULL, &PackageFilename))
//	{
//		FAssetData AssetData = FAutomationEditorCommonUtils::GetAssetDataFromPackagePath(PackageFilename);
//		FName ObjectFullName = FName(*AssetData.GetFullName());
//		
//		FThumbnailMap ThumbnailMap;
//
//		const FObjectThumbnail* ThumbnailPtr = ThumbnailTools::FindCachedThumbnail(ObjectFullName.ToString());
//		if (!ThumbnailPtr)
//		{
//			TSet<FName> ObjectFullNames;
//			ObjectFullNames.Add(ObjectFullName);
//			ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames, ThumbnailMap);
//			ThumbnailPtr = ThumbnailMap.Find(ObjectFullName);
//		}
//		if (ThumbnailPtr)
//		{
//			static TSharedPtr<FSlateDynamicImageBrush> DynamicBrush = FSlateDynamicImageBrush::CreateWithImageData(
//				ObjectFullName,
//				FVector2D(ThumbnailPtr->GetImageWidth(), ThumbnailPtr->GetImageHeight()),
//				ThumbnailPtr->GetUncompressedImageData());
//			if (DynamicBrush.IsValid() && ThumbnailPtr->GetUncompressedImageData().Num() > 0)
//			{
//				ShowImage->SetImage(DynamicBrush.Get());
//			}
//		}
//	}
//	return
//		SNew(SBox)
//		.WidthOverride(100)
//		.HeightOverride(100)
//		[
//			SNew(SBorder)
//			.Padding(0)
//			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
//			.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
//			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
//			[
//				ShowImage.ToSharedRef()
//			]
//		];
//	
//}
