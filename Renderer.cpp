#include "Renderer.h"
#include "ConstantBuffers.h"

Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
{
    m_deviceResources = deviceResources;
    shaderPath = L"Shaders/shader.hlsl";
}

void Renderer::CreateDeviceDependentResources()
{
    CreateShaders();
    CreateConstantBuffers();
    SetBuffers();
    CreateViewAndPerspective();
}

void Renderer::PassSceneComponents(std::vector<SceneComponent>* components)
{
    sceneComponents = components;
}

void Renderer::Render()
{
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();
    ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargetView();

    float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    context->ClearRenderTargetView(renderTarget, color);
    context->OMSetRenderTargets(1, &renderTarget, nullptr);

    UINT strides[] = { 32 };
    UINT offsets[] = { 0 };

    for (SceneComponent item : *sceneComponents)
    {
        DirectX::XMFLOAT4 position = item.GetPosition();
        SetPosition({ position.x, position.y * aspectRatioXY, 0, 0 });

        std::shared_ptr<RenderData> renderData = item.GetRenderComponent();

        context->IASetIndexBuffer(renderData->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
        context->IASetVertexBuffers(0, 1, renderData->GetVertexBufferAdress(), strides, offsets);
        context->DrawIndexed(renderData->GetIndicesCount(), 0, 0);
    }

    context->OMSetRenderTargets(0, nullptr, nullptr);
}

HRESULT Renderer::CreateShaders()
{
    // Compiling shaders
    char* compileErrors = nullptr;

    ID3DBlob* errorVertexCode = nullptr;
    ID3DBlob* compiledVertexBlob = nullptr;

    HRESULT result = D3DCompileFromFile(shaderPath.c_str(),
        nullptr /*macros*/,
        nullptr /*include*/,
        "VSMain",
        "vs_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &compiledVertexBlob,
        &errorVertexCode);

    if (FAILED(result)) {
        if (errorVertexCode) {
            compileErrors = (char*)(errorVertexCode->GetBufferPointer());
            std::cout << compileErrors << std::endl;
        }
        else
            std::cout << "Missing vertex shader file" << std::endl;

        return result;
    }

    D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

    ID3DBlob* compiledPixelBlob = nullptr;
    ID3DBlob* errorPixelCode;
    result = D3DCompileFromFile(
        shaderPath.c_str(),
        Shader_Macros /*macros*/,
        nullptr /*include*/,
        "PSMain",
        "ps_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &compiledPixelBlob,
        &errorPixelCode);

    if (FAILED(result))
    {
        if (errorPixelCode)
        {
            compileErrors = (char*)(errorPixelCode->GetBufferPointer());
            std::cout << compileErrors << std::endl;
        }
        else
            std::cout << "Missing pixel shader file" << std::endl;

        return result;
    }

    // Creating shaders
    ID3D11Device* device = m_deviceResources->GetDevice();

    result = device->CreateVertexShader(
        compiledVertexBlob->GetBufferPointer(),
        compiledVertexBlob->GetBufferSize(),
        nullptr, &m_pVertexShader);

    result = device->CreatePixelShader(
        compiledPixelBlob->GetBufferPointer(),
        compiledPixelBlob->GetBufferSize(),
        nullptr, &m_pPixelShader);

    // Creating input layout
    D3D11_INPUT_ELEMENT_DESC inputElements[] = {
        D3D11_INPUT_ELEMENT_DESC {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0},
        D3D11_INPUT_ELEMENT_DESC {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0}
    };

    result = device->CreateInputLayout(
        inputElements,
        2,
        compiledVertexBlob->GetBufferPointer(),
        compiledVertexBlob->GetBufferSize(),
        &m_pInputLayout);

    return result;
}

HRESULT Renderer::CreateConstantBuffers()
{
    HRESULT result = S_OK;

    ID3D11Device* device = m_deviceResources->GetDevice();

    D3D11_BUFFER_DESC position_buffer_desc = {};
    position_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    position_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    position_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    position_buffer_desc.MiscFlags = 0;
    position_buffer_desc.StructureByteStride = 0;
    position_buffer_desc.ByteWidth = sizeof(PositionBuffer);
    result = device->CreateBuffer(&position_buffer_desc, nullptr, &positionBuffer);

    D3D11_BUFFER_DESC display_buffer_desc = {};
    display_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    display_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    display_buffer_desc.CPUAccessFlags = 0;
    display_buffer_desc.MiscFlags = 0;
    display_buffer_desc.StructureByteStride = 0;
    display_buffer_desc.ByteWidth = sizeof(DisplayBuffer);
    result = device->CreateBuffer(&display_buffer_desc, nullptr, &displayBuffer);

    return result;
}

HRESULT Renderer::CreateSquare()
{
    HRESULT result = S_OK;
    ID3D11Device* device = m_deviceResources->GetDevice();

    //Vertex buffer
    DirectX::XMFLOAT4 points[8] = {
        DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
        DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f),DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
        DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
        DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
    };

    D3D11_BUFFER_DESC vertexBufDesc = {};
    vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufDesc.CPUAccessFlags = 0;
    vertexBufDesc.MiscFlags = 0;
    vertexBufDesc.StructureByteStride = 0;
    vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * std::size(points);

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = points;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    result = device->CreateBuffer(&vertexBufDesc, &vertexData, &m_pVertexBuffer);

    // Index buffer
    int indices[] = { 0,1,2, 1,0,3 };
    D3D11_BUFFER_DESC indexBufDesc = {};
    indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufDesc.CPUAccessFlags = 0;
    indexBufDesc.MiscFlags = 0;
    indexBufDesc.StructureByteStride = 0;
    indexBufDesc.ByteWidth = sizeof(int) * std::size(indices);

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    result = device->CreateBuffer(&indexBufDesc, &indexData, &m_pIndexBuffer);

    return result;
}

void Renderer::SetBuffers()
{
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

    ID3D11Buffer** buffers = new ID3D11Buffer* []{ positionBuffer.Get(), displayBuffer.Get() };

    context->IASetInputLayout(m_pInputLayout.Get());
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetConstantBuffers(0, 1, positionBuffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, displayBuffer.GetAddressOf());
    context->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
}

void Renderer::SetPosition(PositionBuffer position_data)
{
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

    D3D11_MAPPED_SUBRESOURCE resource = {};
    context->Map(positionBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    auto data = reinterpret_cast<float*>(resource.pData);
    memcpy(data, &position_data, sizeof(PositionBuffer));
    context->Unmap(positionBuffer.Get(), 0);
}

void Renderer::SetDisplayAspects(DisplayBuffer display_data)
{
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

    context->UpdateSubresource(displayBuffer.Get(), 0, nullptr, &display_data, 0, 0);

    aspectRatioXY = display_data.x_aspect / display_data.y_aspect;
    /*D3D11_MAPPED_SUBRESOURCE resource = {};
    context->Map(displayBuffer.Get(), 1, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    auto data = reinterpret_cast<float*>(resource.pData);
    memcpy(data, &display_data, sizeof(DisplayBuffer));
    context->Unmap(displayBuffer.Get(), 1);*/
}

void Renderer::CreateViewAndPerspective()
{
    ID3D11Device* device = m_deviceResources->GetDevice();
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

    CD3D11_RASTERIZER_DESC rastDesc = {};
    rastDesc.CullMode = D3D11_CULL_NONE;
    rastDesc.FillMode = D3D11_FILL_SOLID;

    ID3D11RasterizerState* rastState;
    HRESULT result = device->CreateRasterizerState(&rastDesc, &rastState);

    context->RSSetState(rastState);

    D3D11_VIEWPORT viewport = {};
    viewport.Width = 640; 
    viewport.Height = 320;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);

    aspect_coefficient = min(viewport.Width, viewport.Height);

    SetDisplayAspects({ viewport.Width / aspect_coefficient , viewport.Height / aspect_coefficient, 0, 0 });
}
