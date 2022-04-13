#pragma once
#include "RenderData.h"

class Material;

class CommonRenderData :public RenderData
{
public:
    CommonRenderData(Material* material, size_t vertex_stride = 32) :indices_count(0), stride(vertex_stride), RenderData(material) {};
    ID3D11Buffer* GetVertexBuffer() override;
    ID3D11Buffer** GetVertexBufferAddress() override;
    ID3D11Buffer* GetIndexBuffer() override;
    int GetIndicesCount() override;
    void SetBuffers(ID3D11DeviceContext* context) override;

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
    size_t stride;
    int indices_count;
};