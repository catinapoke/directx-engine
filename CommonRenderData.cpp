#include "CommonRenderData.h"
#include "Material.h"

ID3D11Buffer* CommonRenderData::GetVertexBuffer()
{
    return m_pVertexBuffer.Get();
}

ID3D11Buffer** CommonRenderData::GetVertexBufferAdress()
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