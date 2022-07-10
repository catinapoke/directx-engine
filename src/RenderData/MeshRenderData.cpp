#include "MeshRenderData.h"

void MeshRenderData::ConvertToBuffers(ID3D11Device* device, Mesh* mesh)
{
    const size_t vertex_size = std::size(mesh->vertices) * sizeof(mesh->vertices[0]);

    CreateVertexBuffer(m_pVertexBuffer, device, (void*)mesh->vertices.data(), vertex_size);
    CreateIndexBuffer(m_pIndexBuffer, device, (int*)mesh->indices.data(), std::size(mesh->indices));

    indices_count = std::size(mesh->indices);
}
