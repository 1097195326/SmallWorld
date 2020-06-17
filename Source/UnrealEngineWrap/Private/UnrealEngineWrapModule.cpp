#include "UnrealEngineWrapModule.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FUnrealEngineWrapModule"

void FUnrealEngineWrapModule::StartupModule()
{
}

void FUnrealEngineWrapModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealEngineWrapModule, UnrealEngineWrap);
