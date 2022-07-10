#pragma once
#include <memory>
#include "../Core/DeviceResources.h"
#include "../Components/Camera.h"
#include "../Core/Material.h"

class TransformComponent;

class Basic3DMaterial : public Material
{
public:
    Basic3DMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_3d.hlsl", 
        InputScheme scheme = InputLayoutSchemes::PositionColor)
        :Material(resources, shader, scheme), camera_(nullptr)
    {
        CreateShader();
        CreateBuffers();
    };

    HRESULT CreateBuffers() override;
    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;

    void SetCamera(CameraComponent* camera) { this->camera_ = camera; };

protected:
    virtual void SetProjectionViewMatrix();
    void SetModelMatrix(TransformComponent* transform);

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> camera_buffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> model_buffer;

    CameraComponent* camera_;
};