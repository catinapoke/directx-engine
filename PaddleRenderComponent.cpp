#include "PaddleRenderComponent.h"
#include <array>

PaddleRenderComponent::PaddleRenderComponent(ID3D11Device* device):RenderData(nullptr)
{
    //Vertex buffer
    DirectX::XMFLOAT4 points[8] = {
        DirectX::XMFLOAT4( 0.075f,  0.4f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
        DirectX::XMFLOAT4(-0.075f, -0.4f, 0.5f, 1.0f),  DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
        DirectX::XMFLOAT4( 0.075f, -0.4f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
        DirectX::XMFLOAT4(-0.075f,  0.4f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
    };

    // Index buffer
    int indices[] = { 0,1,2, 1,0,3 };

    CreateVertexBuffer(m_pVertexBuffer, device, points, std::size(points));
    CreateIndexBuffer(m_pIndexBuffer, device, indices, std::size(indices));

    indices_count = std::size(indices);
}

ID3D11Buffer* PaddleRenderComponent::GetVertexBuffer()
{
    return m_pVertexBuffer.Get();
}

ID3D11Buffer** PaddleRenderComponent::GetVertexBufferAdress()
{
    return m_pVertexBuffer.GetAddressOf();
}

ID3D11Buffer* PaddleRenderComponent::GetIndexBuffer()
{
    return m_pIndexBuffer.Get();
}

int PaddleRenderComponent::GetIndicesCount()
{
    return indices_count;
}
