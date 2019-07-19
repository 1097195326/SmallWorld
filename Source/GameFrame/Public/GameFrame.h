#pragma once

#include "Modules/ModuleInterface.h"

class GameFrameModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};