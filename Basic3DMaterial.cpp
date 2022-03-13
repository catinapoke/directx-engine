#include "Basic3DMaterial.h"
#include "InputDevice\SimpleMath.h"
#include "TransformComponent.h"


HRESULT Basic3DMaterial::CreateInputLayout(ID3DBlob* compiledVertexBlob)
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

HRESULT Basic3DMaterial::CreateBuffers()
{
    ID3D11Device* device = device_resources->GetDevice();
    HRESULT result = S_OK;

    D3D11_BUFFER_DESC matrix_buffer_desc = {};
    matrix_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    matrix_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrix_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrix_buffer_desc.MiscFlags = 0;
    matrix_buffer_desc.StructureByteStride = 0;
    matrix_buffer_desc.ByteWidth = sizeof(Matrix);
    result = device->CreateBuffer(&matrix_buffer_desc, nullptr, &camera_buffer);
    result = device->CreateBuffer(&matrix_buffer_desc, nullptr, &model_buffer);

    return result;
}

void Basic3DMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetConstantBuffers(0, 1, camera_buffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, model_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);

    SetProjectionViewMatrix();
}

void Basic3DMaterial::PrepareObjectData(SceneActor* actor)
{
    SetModelMatrix(actor->GetTransform());
}

void Basic3DMaterial::SetProjectionViewMatrix()
{
    Matrix matrix = camera->GetProjectionViewMatrix().Transpose();
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    D3D11_MAPPED_SUBRESOURCE resource = {};
    context->Map(camera_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    auto data = reinterpret_cast<float*>(resource.pData);
    memcpy(data, &matrix, sizeof(Matrix));
    context->Unmap(camera_buffer.Get(), 0);
}

void Basic3DMaterial::SetModelMatrix(TransformComponent* transform)
{
    Matrix matrix = transform->GetWorldModelMatrix().Transpose();
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    D3D11_MAPPED_SUBRESOURCE resource = {};
    context->Map(model_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    auto data = reinterpret_cast<float*>(resource.pData);
    memcpy(data, &matrix, sizeof(Matrix));
    context->Unmap(model_buffer.Get(), 0);
}
