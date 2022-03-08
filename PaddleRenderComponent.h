#pragma once
#include <wrl.h>
#include "RenderData.h"
class PaddleRenderComponent :public RenderData
{
public:
    PaddleRenderComponent():indices_count(0) {};
    PaddleRenderComponent(ID3D11Device* device);
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer** GetVertexBufferAdress();
    ID3D11Buffer* GetIndexBuffer();
    int GetIndicesCount();

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
    int indices_count;
};