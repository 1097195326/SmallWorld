#pragma once

#include "Modules/ModuleInterface.h"

class FUnrealEngineWrapModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};