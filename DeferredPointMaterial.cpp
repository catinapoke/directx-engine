#include "DeferredPointMaterial.h"

#include <iostream>

#include "Camera.h"
#include "LightRenderData.h"
#include "TransformComponent.h"

void DeferredPointMaterial::SetCamera(CameraComponent* camera)
{
    camera_ = camera;
}

void DeferredPointMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetConstantBuffers(0, 1, transform_buffer.GetAddressOf());
    context->PSSetConstantBuffers(1, 1, light_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);

    transform_data[1] = camera_->GetProjectionViewMatrix().Transpose();
}

void DeferredPointMaterial::PrepareObjectData(SceneActor* actor)
{
    TransformComponent* transform = actor->GetTransform();
    transform_data[0] = transform->GetWorldModelMatrix().Transpose();
    MapBuffer(transform_buffer.Get(), transform_data, sizeof(transform_data));

    LightRenderData* data = dynamic_cast<LightRenderData*>(actor->GetRenderData().get());
    if(data == nullptr)
    {
        std::cout << "Point: LightRenderData convert error!\n";
        return;
    }

    Vector4 light_data[3] =
    {
        Vector4(transform->GetLocalPosition()),
        Vector4(data->GetColor()),
        Vector4(camera_->GetActor()->GetComponent<TransformComponent>()->GetWorldPosition())
    };
    MapBuffer(light_buffer.Get(), light_data, sizeof(light_data));
}

HRESULT DeferredPointMaterial::CreateBuffers()
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

    buffer_desc.ByteWidth = sizeof(Vector4)*3;
    result = device->CreateBuffer(&buffer_desc, nullptr, &light_buffer);

    return result;
}
