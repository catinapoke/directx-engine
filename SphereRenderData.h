#pragma once
#include "RenderData.h"

class SphereRenderData :public RenderData
{
public:
    SphereRenderData(Material* material) :indices_count(0), RenderData(material) {};
    SphereRenderData(ID3D11Device* device, Material* material);
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer** GetVertexBufferAdress();
    ID3D11Buffer* GetIndexBuffer();
    int GetIndicesCount();

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
    int indices_count;
};