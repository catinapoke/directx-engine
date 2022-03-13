#include "Material.h"
#include <d3dcompiler.h>
#include <iostream>


HRESULT Material::CreateShader()
{
    // Compiling shaders
    char* compileErrors = nullptr;

    ID3DBlob* errorVertexCode = nullptr;
    ID3DBlob* compiledVertexBlob = nullptr;

    HRESULT result = D3DCompileFromFile(shader_name.c_str(),
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

    //D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

    ID3DBlob* compiledPixelBlob = nullptr;
    ID3DBlob* errorPixelCode;
    result = D3DCompileFromFile(
        shader_name.c_str(),
        nullptr /*macros Shader_Macros*/,
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
    ID3D11Device* device = device_resources->GetDevice();

    result = device->CreateVertexShader(
        compiledVertexBlob->GetBufferPointer(),
        compiledVertexBlob->GetBufferSize(),
        nullptr, &vertex_shader);

    result = device->CreatePixelShader(
        compiledPixelBlob->GetBufferPointer(),
        compiledPixelBlob->GetBufferSize(),
        nullptr, &pixel_shader);

    return CreateInputLayout(compiledVertexBlob);
}

// Basic layout
HRESULT Material::CreateInputLayout(ID3DBlob* compiledVertexBlob)
{
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

    return device_resources->GetDevice()->CreateInputLayout(
        inputElements,
        2,
        compiledVertexBlob->GetBufferPointer(),
        compiledVertexBlob->GetBufferSize(),
        &input_layout);
}
