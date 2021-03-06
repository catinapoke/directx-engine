#include "InputLayoutSchemes.h"

const InputScheme InputLayoutSchemes::Position = {
   D3D11_INPUT_ELEMENT_DESC {
       "POSITION",
       0,
       DXGI_FORMAT_R32G32B32A32_FLOAT,
       0,
       0,
       D3D11_INPUT_PER_VERTEX_DATA,
       0}
};

const InputScheme InputLayoutSchemes::PositionColor = {
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

const InputScheme InputLayoutSchemes::PositionTexture = {
    D3D11_INPUT_ELEMENT_DESC {
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        0,
        D3D11_INPUT_PER_VERTEX_DATA,
        0
    },
    D3D11_INPUT_ELEMENT_DESC {
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D11_APPEND_ALIGNED_ELEMENT,
        D3D11_INPUT_PER_VERTEX_DATA,
        0,
    }
};

const InputScheme InputLayoutSchemes::PositionTextureNormal = {
    D3D11_INPUT_ELEMENT_DESC {
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        0,
        D3D11_INPUT_PER_VERTEX_DATA,
        0
    },
    D3D11_INPUT_ELEMENT_DESC {
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D11_APPEND_ALIGNED_ELEMENT,
        D3D11_INPUT_PER_VERTEX_DATA,
        0,
    },
    D3D11_INPUT_ELEMENT_DESC {
        "NORMAL",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D11_APPEND_ALIGNED_ELEMENT,
        D3D11_INPUT_PER_VERTEX_DATA,
        0
    },
};