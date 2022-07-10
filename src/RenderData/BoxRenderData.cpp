#include "BoxRenderData.h"
#include <vector>


BoxRenderData::BoxRenderData(ID3D11Device* device, Material* material):CommonRenderData(material)
{
    //Vertex buffer
    DirectX::XMFLOAT4 points[16] =
    {
        DirectX::XMFLOAT4(-0.5f, 0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), // +Y (top face)
        DirectX::XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
        DirectX::XMFLOAT4(0.5f, 0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        DirectX::XMFLOAT4(-0.5f, 0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),

        DirectX::XMFLOAT4(-0.5f, -0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), // -Y (bottom face)
        DirectX::XMFLOAT4(0.5f, -0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
        DirectX::XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
        DirectX::XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)

    };

    // Index buffer
    int indices[36] = { 0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    3, 2, 5,
    3, 5, 4,

    2, 1, 6,
    2, 6, 5,

    1, 7, 6,
    1, 0, 7,

    0, 3, 4,
    0, 4, 7 };

    CreateVertexBuffer(m_pVertexBuffer, device, points, (int)std::size(points));
    CreateIndexBuffer(m_pIndexBuffer, device, indices, std::size(indices));

    indices_count = std::size(indices);
}