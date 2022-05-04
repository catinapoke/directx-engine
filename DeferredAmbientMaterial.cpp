#include "DeferredAmbientMaterial.h"

#include <iostream>

#include "AmbientRenderData.h"
#include "InputDevice/SimpleMath.h"

void DeferredAmbientMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();
    device_resources->SetCullNoneSolidState();
    device_resources->SetDepthLightScreenState();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->PSSetConstantBuffers(0, 1, light_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);
}

void DeferredAmbientMaterial::PrepareObjectData(SceneActor* actor)
{
    AmbientRenderData* data = dynamic_cast<AmbientRenderData*>(actor->GetRenderData().get());
    if (data == nullptr)
    {
        std::cout << "AmbientRenderData convert error!\n";
        return;
    }

    DirectX::XMFLOAT3 color = data->GetColor();
    float strength = data->GetStrength();

    float light_data[4] =
    {
        color.x, color.y, color.z, strength
    };
    MapBuffer(light_buffer.Get(), light_data, sizeof(light_data));
}

HRESULT DeferredAmbientMaterial::CreateBuffers()
{
    ID3D11Device* device = device_resources->GetDevice();
    HRESULT result = S_OK;

    D3D11_BUFFER_DESC buffer_desc = {};
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = 0;
    buffer_desc.StructureByteStride = 0;

    buffer_desc.ByteWidth = sizeof(DirectX::SimpleMath::Vector4);
    result = device->CreateBuffer(&buffer_desc, nullptr, &light_buffer);

    return result;
}
