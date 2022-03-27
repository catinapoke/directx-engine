#include "MeshRenderData.h"

void MeshRenderData::ConvertToBuffers(ID3D11Device* device, Mesh* mesh)
{
    // TODO: Handle passing size and count
    CreateVertexBuffer(m_pVertexBuffer, device, points, std::size(points));
    CreateIndexBuffer(m_pIndexBuffer, device, indices, std::size(indices));

    indices_count = std::size(indices);
}
