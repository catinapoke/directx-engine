#pragma once
#include "MeshMaterial.h"

class LightComponent;

class PhongMeshMaterial : public Material
{
public:
    PhongMeshMaterial(std::shared_ptr<DeviceResources> resources, 
        std::wstring shader = L"Shaders/shader_mesh_light.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
            :Material(resources, shader, scheme)
    {
        CreateShader();
        PhongMeshMaterial::CreateBuffers();
        sampler = new Sampler(resources->GetDevice(), resources->GetDeviceContext());
    };

    HRESULT CreateBuffers() override;
    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;

    void SetLight(LightComponent* light);
    void SetCamera(CameraComponent* camera);

protected:
    void SaveModelMatrices(TransformComponent* transform);
    void SaveProjectionViewMatrix();
    void MapTransformData();

    void SetLightBuffer();
    void SetMaterialBuffer(std::shared_ptr<RenderData> render_data);

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> transform_buffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> material_buffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> light_buffer;
    Sampler* sampler;

    LightComponent* light_ = nullptr;
    CameraComponent* camera_ = nullptr;

    Matrix transform_data[3];
};
