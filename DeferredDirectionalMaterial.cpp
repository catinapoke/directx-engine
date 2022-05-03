#include "DeferredDirectionalMaterial.h"

#include <iostream>

#include "Camera.h"
#include "LightRenderData.h"
#include "TransformComponent.h"

void DeferredDirectionalMaterial::SetCamera(CameraComponent* camera)
{
    camera_ = camera;
}

void DeferredDirectionalMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->PSSetConstantBuffers(0, 1, light_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);
}

void DeferredDirectionalMaterial::PrepareObjectData(SceneActor* actor)
{
    LightRenderData* data = dynamic_cast<LightRenderData*>(actor->GetRenderData().get());
    if (data == nullptr)
    {
        std::cout << "Directional: LightRenderData convert error!\n";
        return;
    }

    TransformComponent* transform = actor->GetTransform();
    Vector4 light_data[3] =
    {
        Vector4(transform->GetForward()),
        Vector4(data->GetColor()),
        Vector4(camera_->GetActor()->GetComponent<TransformComponent>()->GetWorldPosition())
    };
    MapBuffer(light_buffer.Get(), light_data, sizeof(light_data));
}

HRESULT DeferredDirectionalMaterial::CreateBuffers()
{
    ID3D11Device* device = device_resources->GetDevice();
    HRESULT result = S_OK;

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = 0;
    buffer_desc.StructureByteStride = 0;

    buffer_desc.ByteWidth = sizeof(Vector4) * 3;
    result = device->CreateBuffer(&buffer_desc, nullptr, &light_buffer);

    return result;
}
