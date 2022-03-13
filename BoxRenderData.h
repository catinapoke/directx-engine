#pragma once

#include <wrl.h>
#include "RenderData.h"
class BoxRenderData :public RenderData
{
public:
    BoxRenderData(Material* material) :indices_count(0), RenderData(material) {};
    BoxRenderData(ID3D11Device* device, Material* material);
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer** GetVertexBufferAdress();
    ID3D11Buffer* GetIndexBuffer();
    int GetIndicesCount();

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
    int indices_count;
};