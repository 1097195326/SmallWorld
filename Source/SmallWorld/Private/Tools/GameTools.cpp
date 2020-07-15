#include "GameTools.h"

#include "Misc/FileHelper.h"
#include "Internationalization/Regex.h"
#include "ImageWrapper/Public/IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "Modules/ModuleManager.h"


RaceEnum GameTools::GetRaceFromString(FString InRace)
{
	RaceEnum Race = RaceEnum::Race_None;
	if (InRace.Equals(TEXT("Human"))){ Race = Race_Human; }
	else if (InRace.Equals(TEXT("Orc"))) { Race = Race_Orc; }
	else if (InRace.Equals(TEXT("Elf"))) { Race = Race_Elf; }
	else if (InRace.Equals(TEXT("Undead"))) { Race = Race_Undead; }
	return Race;
}
bool GameTools::CheckStringIsValid(const FString& str, const FString& Reg)
{
	FRegexPattern Pattern(Reg);
	FRegexMatcher regMatcher(Pattern, str);
	regMatcher.SetLimits(0, str.Len());
	return regMatcher.FindNext();
}
bool GameTools::CheckPhone(const FString& str)
{
	if (str.Len() != 11) return false;
	FString reg = TEXT("^1\\d{10}$");
	return GameTools::CheckStringIsValid(str, reg);
}
bool GameTools::IsNumber(const FString& str)
{
	FString reg = TEXT("^[0-9]$");
	return GameTools::CheckStringIsValid(str, reg);
}
//UTexture2D* GameTools::LoadImageFromDisk(UObject* Outer, const FString& ImagePath)
//{
//	static IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
//	// Check if the file exists first
//	if (!FPaths::FileExists(ImagePath))
//	{
//		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *ImagePath);
//		return nullptr;
//	}
//
//	// Load the compressed byte data from the file
//	TArray<uint8> FileData;
//	if (!FFileHelper::LoadFileToArray(FileData, *ImagePath))
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *ImagePath);
//		return nullptr;
//	}
//
//	// Detect the image type using the ImageWrapper module
//	EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(FileData.GetData(), FileData.Num());
//	if (ImageFormat == EImageFormat::Invalid)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Unrecognized image file format: %s"), *ImagePath);
//		return nullptr;
//	}
//
//	// Create an image wrapper for the detected image format
//	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
//	if (!ImageWrapper.IsValid())
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to create image wrapper for file: %s"), *ImagePath);
//		return nullptr;
//	}
//
//	// Decompress the image data
//	const TArray<uint8>* RawData = nullptr;
//	ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num());
//	ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData);
//	if (RawData == nullptr)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to decompress image file: %s"), *ImagePath);
//		return nullptr;
//	}
//
//	// Create the texture and upload the uncompressed image data
//	FString TextureBaseName = TEXT("Texture_") + FPaths::GetBaseFilename(ImagePath);
//	return CreateTexture(Outer, *RawData, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8, FName(*TextureBaseName));
//}
//UTexture2D* GameTools::CreateTexture(UObject* Outer, const TArray<uint8>& PixelData, int32 InSizeX, int32 InSizeY, EPixelFormat InFormat, FName BaseName)
//{
//	// Shamelessly copied from UTexture2D::CreateTransient with a few modifications
//	if (InSizeX <= 0 || InSizeY <= 0 ||
//		(InSizeX % GPixelFormats[InFormat].BlockSizeX) != 0 ||
//		(InSizeY % GPixelFormats[InFormat].BlockSizeY) != 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Invalid parameters specified for UImageLoader::CreateTexture()"));
//		return nullptr;
//	}
//
//	// Most important difference with UTexture2D::CreateTransient: we provide the new texture with a name and an owner
//	FName TextureName = MakeUniqueObjectName(Outer, UTexture2D::StaticClass(), BaseName);
//	UTexture2D* NewTexture = NewObject<UTexture2D>(Outer, TextureName, RF_Transient);
//
//	NewTexture->PlatformData = new FTexturePlatformData();
//	NewTexture->PlatformData->SizeX = InSizeX;
//	NewTexture->PlatformData->SizeY = InSizeY;
//	NewTexture->PlatformData->PixelFormat = InFormat;
//
//	// Allocate first mipmap and upload the pixel data
//	int32 NumBlocksX = InSizeX / GPixelFormats[InFormat].BlockSizeX;
//	int32 NumBlocksY = InSizeY / GPixelFormats[InFormat].BlockSizeY;
//
//	FTexture2DMipMap* Mip = new FTexture2DMipMap();
//	//FTexture2DMipMap* Mip = new(NewTexture->PlatformData->Mips) FTexture2DMipMap();
//	Mip->SizeX = InSizeX;
//	Mip->SizeY = InSizeY;
//	Mip->BulkData.Lock(LOCK_READ_WRITE);
//	void* TextureData = Mip->BulkData.Realloc(NumBlocksX * NumBlocksY * GPixelFormats[InFormat].BlockBytes);
//	FMemory::Memcpy(TextureData, PixelData.GetData(), PixelData.Num());
//	Mip->BulkData.Unlock();
//
//	NewTexture->UpdateResource();
//	return NewTexture;
//}
