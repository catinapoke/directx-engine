#pragma once
#include <string>
#include <memory>
#include "DeviceResources.h"
#include "InputLayoutSchemes.h"
#include "SceneActor.h"

class Material
{
public:
    Material(std::shared_ptr<DeviceResources> resources, std::wstring shader, InputScheme scheme = InputLayoutSchemes::PositionColor)
        :shader_name(shader), device_resources(resources), input_scheme(scheme) {};

    virtual void PrepareRender() = 0; // Set Shaders, buffers
    virtual void PrepareObjectData(SceneActor* actor) = 0;

protected:
    HRESULT CreateShader();
    virtual HRESULT CreateInputLayout(ID3DBlob* compiledVertexBlob);
    virtual HRESULT CreateBuffers() = 0;

protected:
    std::wstring shader_name;
    InputScheme input_scheme;
    std::shared_ptr<DeviceResources> device_resources;

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>  pixel_shader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  input_layout;
};