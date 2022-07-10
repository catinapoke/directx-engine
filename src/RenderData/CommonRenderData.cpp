#include "CommonRenderData.h"
#include "../Core/Material.h"

ID3D11Buffer* CommonRenderData::GetVertexBuffer()
{
    return m_pVertexBuffer.Get();
}

ID3D11Buffer** CommonRenderData::GetVertexBufferAddress()
{
    return m_pVertexBuffer.GetAddressOf();
}

ID3D11Buffer* CommonRenderData::GetIndexBuffer()
{
    return m_pIndexBuffer.Get();
}

int CommonRenderData::GetIndicesCount()
{
    return indices_count;
}

void CommonRenderData::SetBuffers(ID3D11DeviceContext* context)
{
    UINT strides[] = { static_cast<UINT>(stride) };
    UINT offsets[] = { 0 };
    context->IASetIndexBuffer(GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetVertexBuffers(0, 1, GetVertexBufferAddress(), strides, offsets);
}
