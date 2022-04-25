#include "Basic3DMaterial.h"
#include "InputDevice\SimpleMath.h"
#include "TransformComponent.h"
#include "InputLayoutSchemes.h"


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
    context->VSSetConstantBuffers(0, 1, model_buffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, camera_buffer.GetAddressOf());
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
    Matrix matrix = camera_->GetProjectionViewMatrix().Transpose();
    MapBuffer(camera_buffer.Get(), &matrix, sizeof(Matrix));
}

void Basic3DMaterial::SetModelMatrix(TransformComponent* transform)
{
    Matrix matrix = transform->GetWorldModelMatrix().Transpose();
    MapBuffer(model_buffer.Get(), &matrix, sizeof(Matrix));
}
