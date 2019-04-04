#pragma once

#include "Modules/ModuleInterface.h"

class ProceduralMeshModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};