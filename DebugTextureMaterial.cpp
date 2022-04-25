#include "DebugTextureMaterial.h"

HRESULT DebugTextureMaterial::CreateBuffers()
{
    return S_OK;
}

void DebugTextureMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);
}

void DebugTextureMaterial::PrepareObjectData(SceneActor* actor)
{
}
