#pragma once
#include <memory>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <iostream>
#include <chrono>
#include <vector>

#include "DeviceResources.h"
#include "SceneComponent.h"
#include "ConstantBuffers.h"

class Renderer
{
public:
    Renderer(std::shared_ptr<DeviceResources> deviceResources);
    ~Renderer() {};

    void CreateDeviceDependentResources();
    void PassSceneComponents(std::vector<SceneComponent>* components);
    void CreateWindowSizeDependentResources();
    void Render();

    int GetAspectCoefficient() { return aspect_coefficient;}

private:
    void SetBuffers();
    void SetPosition(PositionBuffer position_data);
    void SetDisplayAspects(DisplayBuffer display_data);

    HRESULT CreateShaders();
    HRESULT CreateConstantBuffers();
    HRESULT CreateSquare();
    void    CreateViewAndPerspective();

private:
    std::vector<SceneComponent>* sceneComponents;
    std::shared_ptr<DeviceResources> m_deviceResources;

    Microsoft::WRL::ComPtr<ID3D11Buffer>* vBuffers;
    Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pIndexBuffer;
    Microsoft::WRL::ComPtr<ID3D11VertexShader>      m_pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>       m_pPixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_pInputLayout;

    Microsoft::WRL::ComPtr<ID3D11Buffer> positionBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> displayBuffer;

    std::wstring shaderPath;
    float aspect_coefficient = 256;
    float aspectRatioXY = 1;
};