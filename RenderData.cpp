#include "RenderData.h"
#include "Material.h"

RenderData::RenderData(Material* material)
{
    this->material = material;
}

Material* RenderData::GetMaterial()
{
    return material;
}

HRESULT RenderData::CreateVertexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, ID3D11Device* device, DirectX::XMFLOAT4* points, int arraySize)
{
    return CreateVertexBuffer(buffer, device, (void*)points, sizeof(DirectX::XMFLOAT4) * arraySize);
}

HRESULT RenderData::CreateVertexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, ID3D11Device* device, void* points, size_t data_size)
{
    D3D11_BUFFER_DESC vertexBufDesc = {};
    vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufDesc.CPUAccessFlags = 0;
    vertexBufDesc.MiscFlags = 0;
    vertexBufDesc.StructureByteStride = 0;
    vertexBufDesc.ByteWidth = data_size;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = points;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    return device->CreateBuffer(&vertexBufDesc, &vertexData, &buffer);
}

HRESULT RenderData::CreateIndexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, ID3D11Device* device, int* indices, int arraySize)
{
    D3D11_BUFFER_DESC indexBufDesc = {};
    indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufDesc.CPUAccessFlags = 0;
    indexBufDesc.MiscFlags = 0;
    indexBufDesc.StructureByteStride = 0;
    indexBufDesc.ByteWidth = sizeof(int) * arraySize;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    return device->CreateBuffer(&indexBufDesc, &indexData, &buffer);
}
