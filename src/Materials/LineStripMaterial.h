#pragma once
#include "Basic3DMaterial.h"

class LineStripMaterial : public Basic3DMaterial
{
public:
    LineStripMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_3d.hlsl")
        :Basic3DMaterial(resources, shader) {}

    void PrepareRender() override;
};