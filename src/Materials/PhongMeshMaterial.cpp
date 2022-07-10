#include "PhongMeshMaterial.h"
#include "../Components/LightComponent.h"
#include "../RenderData/PhongRenderData.h"
#include "../Components/TransformComponent.h"

HRESULT PhongMeshMaterial::CreateBuffers()
{
    ID3D11Device* device = device_resources->GetDevice();
    HRESULT result = S_OK;

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = 0;
    buffer_desc.StructureByteStride = 0;

    buffer_desc.ByteWidth = sizeof(transform_data);
    result = device->CreateBuffer(&buffer_desc, nullptr, &transform_buffer);

    buffer_desc.ByteWidth = sizeof(PhongMaterial);
    result = device->CreateBuffer(&buffer_desc, nullptr, &material_buffer);

    buffer_desc.ByteWidth = sizeof(Vector4) * 3;
    result = device->CreateBuffer(&buffer_desc, nullptr, &light_buffer);

    return result;
}

void PhongMeshMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetConstantBuffers(0, 1, transform_buffer.GetAddressOf());
    context->PSSetConstantBuffers(1, 1, material_buffer.GetAddressOf());
    context->PSSetConstantBuffers(2, 1, light_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);

    SaveProjectionViewMatrix();
    SetLightBuffer();
    sampler->SetSampler();
    sampler_texture->SetSampler(1);
}

void PhongMeshMaterial::PrepareObjectData(SceneActor* actor)
{
    SetMaterialBuffer(actor->GetRenderData());
    SaveModelMatrices(actor->GetTransform());
    MapTransformData();
}

void PhongMeshMaterial::SetLight(LightComponent* light)
{
    light_ = light;
}

void PhongMeshMaterial::SetCamera(CameraComponent* camera)
{
    camera_ = camera;
}

void PhongMeshMaterial::MapTransformData()
{
    MapBuffer(transform_buffer.Get(), transform_data, sizeof(transform_data));
}

void PhongMeshMaterial::SaveProjectionViewMatrix()
{
    transform_data[2] = camera_->GetProjectionViewMatrix().Transpose();
    transform_data[3] = light_->GetProjectionViewMatrix().Transpose();
}

void PhongMeshMaterial::SaveModelMatrices(TransformComponent* transform)
{
    Matrix model_matrix = transform->GetWorldModelMatrix();
    transform_data[0] = model_matrix.Transpose();
    transform_data[1] = model_matrix.Transpose().Invert().Transpose();
}

void PhongMeshMaterial::SetLightBuffer()
{
    Vector4 light_data[3];
    light_data[0] = Vector4(camera_->GetActor()->GetComponent<TransformComponent>()->GetWorldPosition());
    light_data[1] = Vector4(light_->GetDirection());
    light_data[2] = Vector4(light_->GetColor());
    MapBuffer(light_buffer.Get(), light_data, sizeof(light_data));
}

void PhongMeshMaterial::SetMaterialBuffer(std::shared_ptr<RenderData> render_data)
{
    PhongRenderData* phong = dynamic_cast<PhongRenderData*>(render_data.get());

    PhongMaterial data = { 0,0,0,0 };
    if (phong != nullptr)
        data = phong->GetMaterialData();

    MapBuffer(material_buffer.Get(), &data, sizeof(data));
}
