#pragma once
#include "RenderData.h"

class Material;

class CommonRenderData :public RenderData
{
public:
    CommonRenderData(Material* material) :indices_count(0), RenderData(material) {};
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer** GetVertexBufferAdress();
    ID3D11Buffer* GetIndexBuffer();
    int GetIndicesCount();

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
    int indices_count;
};