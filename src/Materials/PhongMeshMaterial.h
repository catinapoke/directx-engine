#pragma once
#include "MeshMaterial.h"

class LightComponent;

class PhongMeshMaterial : public Material
{
public:
    PhongMeshMaterial(std::shared_ptr<DeviceResources> resources, 
        std::wstring shader = L"Shaders/shader_light_shadow.hlsl", //shader_mesh_light
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
            :Material(resources, shader, scheme)
    {
        CreateShader();
        PhongMeshMaterial::CreateBuffers();
        sampler = new Sampler(resources->GetDevice(), resources->GetDeviceContext(), 
            D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
            D3D11_COMPARISON_LESS_EQUAL);

        sampler_texture = new Sampler(resources->GetDevice(), resources->GetDeviceContext());
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
    Sampler* sampler_texture;

    LightComponent* light_ = nullptr;
    CameraComponent* camera_ = nullptr;

    Matrix transform_data[4];
};
