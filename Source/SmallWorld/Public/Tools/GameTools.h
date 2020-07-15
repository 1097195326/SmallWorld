#pragma once
#include "CoreMinimal.h"


class GameTools
{
public:

	static bool CheckStringIsValid(const FString& str, const FString& Reg);
	static bool CheckPhone(const FString& str);
	static bool IsNumber(const FString& str);

	/*static class UTexture2D* LoadImageFromDisk(UObject* Outer, const FString& ImagePath);
	static class UTexture2D* CreateTexture(UObject* Outer, const TArray<uint8>& PixelData, int32 InSizeX, int32 InSizeY, EPixelFormat PixelFormat = EPixelFormat::PF_B8G8R8A8, FName BaseName = NAME_None);
*/
};