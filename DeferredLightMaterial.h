#pragma once
#include "Material.h"

class CameraComponent;

class DeferredLightMaterial : public Material
{
public:
    DeferredLightMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_3d.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
        :Material(resources, shader, scheme)
    {
        CreateShader();
    };

    virtual void SetCamera(CameraComponent* camera) = 0;

    // Screen-Space quad: Ambient, Directional
    // Sphere: Point light
    // Gamma correct pow(x, 1/2.2)
};
