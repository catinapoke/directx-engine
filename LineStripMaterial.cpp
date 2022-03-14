#include "LineStripMaterial.h"

void LineStripMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    context->VSSetConstantBuffers(0, 1, camera_buffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, model_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);

    SetProjectionViewMatrix();
}
