#include "Material2D.h"


HRESULT Material2D::CreateInputLayout(ID3DBlob* compiledVertexBlob)
{
    // Creating input layout
    D3D11_INPUT_ELEMENT_DESC inputElements[] = {
        D3D11_INPUT_ELEMENT_DESC {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0},
        D3D11_INPUT_ELEMENT_DESC {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0}
    };

    return device_resources->GetDevice()->CreateInputLayout(
        inputElements,
        2,
        compiledVertexBlob->GetBufferPointer(),
        compiledVertexBlob->GetBufferSize(),
        &input_layout);
}

HRESULT Material2D::CreateBuffers()
{
    ID3D11Device* device = device_resources->GetDevice();
    HRESULT result = S_OK;

    D3D11_BUFFER_DESC position_buffer_desc = {};
    position_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    position_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    position_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    position_buffer_desc.MiscFlags = 0;
    position_buffer_desc.StructureByteStride = 0;
    position_buffer_desc.ByteWidth = sizeof(PositionBuffer);
    result = device->CreateBuffer(&position_buffer_desc, nullptr, &positionBuffer);

    D3D11_BUFFER_DESC display_buffer_desc = {};
    display_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    display_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    display_buffer_desc.CPUAccessFlags = 0;
    display_buffer_desc.MiscFlags = 0;
    display_buffer_desc.StructureByteStride = 0;
    display_buffer_desc.ByteWidth = sizeof(DisplayBuffer);
    result = device->CreateBuffer(&display_buffer_desc, nullptr, &displayBuffer);

    return result;
}

void Material2D::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetConstantBuffers(0, 1, positionBuffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, displayBuffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);
}

void Material2D::SetPosition(PositionBuffer position_data)
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    D3D11_MAPPED_SUBRESOURCE resource = {};
    context->Map(positionBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    auto data = reinterpret_cast<float*>(resource.pData);
    memcpy(data, &position_data, sizeof(PositionBuffer));
    context->Unmap(positionBuffer.Get(), 0);
}

void Material2D::SetDisplayAspects(DisplayBuffer display_data)
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();
    context->UpdateSubresource(displayBuffer.Get(), 0, nullptr, &display_data, 0, 0);
}
