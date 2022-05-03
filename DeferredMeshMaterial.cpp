#include "DeferredMeshMaterial.h"

#include "Camera.h"
#include "PhongRenderData.h"
#include "TransformComponent.h"

HRESULT DeferredMeshMaterial::CreateBuffers()
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

    buffer_desc.ByteWidth = sizeof(float) * 4;
    result = device->CreateBuffer(&buffer_desc, nullptr, &material_buffer);

    return result;
}

void DeferredMeshMaterial::PrepareRender()
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    context->IASetInputLayout(input_layout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetConstantBuffers(0, 1, transform_buffer.GetAddressOf());
    context->PSSetConstantBuffers(1, 1, material_buffer.GetAddressOf());
    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);

    transform_data[2] = camera_->GetProjectionViewMatrix().Transpose();
}

void DeferredMeshMaterial::PrepareObjectData(SceneActor* actor)
{
    const PhongRenderData* render_data = dynamic_cast<PhongRenderData*>(actor->GetRenderData().get());
    float material_data[4] = {
        render_data->GetMaterialData().shininess,
        render_data->GetMaterialData().specular,
        0,0
    };
    MapBuffer(material_buffer.Get(), material_data, sizeof(material_data));

    const Matrix model_matrix = actor->GetTransform()->GetWorldModelMatrix();
    transform_data[0] = model_matrix.Transpose();
    transform_data[1] = model_matrix.Transpose().Invert().Transpose();
    MapBuffer(transform_buffer.Get(), transform_data, sizeof(transform_data));
}

void DeferredMeshMaterial::SetCamera(CameraComponent* camera)
{
    camera_ = camera;
}
