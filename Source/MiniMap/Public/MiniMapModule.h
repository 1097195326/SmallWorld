#pragma once

#include "Modules/ModuleInterface.h"

class MINIMAP_API MiniMapModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};