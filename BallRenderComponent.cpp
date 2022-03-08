#include "BallRenderComponent.h"
#include <array>

BallRenderComponent::BallRenderComponent(ID3D11Device* device)
{
    //Vertex buffer
    DirectX::XMFLOAT4 points[18] =
    {
        DirectX::XMFLOAT4( 0.0f,    0.0f,   0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4(-0.012f,  0.029f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4( 0.012f,  0.029f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4( 0.029f,  0.012f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4( 0.029f, -0.012f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4( 0.012f, -0.029f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4(-0.012f, -0.029f, 0.5f, 1.0f),    DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4(-0.029f, -0.012f, 0.5f, 1.0f),    DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
        DirectX::XMFLOAT4(-0.029f,  0.012f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
    };

    // Index buffer
    int indices[24] = { 0, 1, 2, 2, 0, 3, 3, 0, 4, 4, 0, 5, 5, 0, 6, 6, 0, 7, 7, 0, 8, 8, 0, 1 };

    CreateVertexBuffer(m_pVertexBuffer, device, points, std::size(points));
    CreateIndexBuffer(m_pIndexBuffer, device, indices, std::size(indices));

    indices_count = std::size(indices);
}

ID3D11Buffer* BallRenderComponent::GetVertexBuffer()
{
    return m_pVertexBuffer.Get();
}

ID3D11Buffer** BallRenderComponent::GetVertexBufferAdress()
{
    return m_pVertexBuffer.GetAddressOf();
}

ID3D11Buffer* BallRenderComponent::GetIndexBuffer()
{
    return m_pIndexBuffer.Get();
}

int BallRenderComponent::GetIndicesCount()
{
    return indices_count;
}
