#pragma once

#include "Modules/ModuleInterface.h"

class SlateUIModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};