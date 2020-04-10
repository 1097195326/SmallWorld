#pragma once

#include "Modules/ModuleInterface.h"

class MiniMapModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};