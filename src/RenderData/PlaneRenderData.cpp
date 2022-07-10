#pragma once
#include <vector>
#include <iostream>
#include "PlaneRenderData.h"
#include "../Core/Material.h"

// DirectX::SimpleMath::Vector4
typedef DirectX::XMFLOAT4 Vector4;


PlaneRenderData::PlaneRenderData(ID3D11Device* device, Material* material, Vector2 square_count, float side_length = 10.f)
    :CommonRenderData(material)
{
    int points_length = 2 * (square_count.x + 1) * (square_count.y + 1);
    int indices_length = 2 * (square_count.x + square_count.y + 2 * (square_count.x * square_count.y));
    //int indices_length = 6 * (square_count.x * square_count.y); // trinagles
    
    Vector4* points = new Vector4[points_length];
    int* indices = new int[indices_length];

    int k = 0;
    for (int y = -(square_count.y * side_length / 2); y <= square_count.y * side_length / 2; y += side_length)
        for (int x = -(square_count.x * side_length / 2); x <= square_count.x * side_length / 2; x += side_length)
        {
            points[k++] = Vector4(x, 0, y, 1); // position
            points[k++] = Vector4(1, 0, 1, 1); // color
        }

    // Lines
    k = 0;
    for (int i = 0; i < square_count.x + 1; i++)
        for (int j = 0; j < square_count.y + 1; j++)
        {
            if (i < square_count.x)
            {
                indices[k++] = i * (square_count.x + 1) + j;
                indices[k++] =(i + 1) * (square_count.x + 1) + j;
            }

            if (j < square_count.y)
            {
                indices[k++] = i * (square_count.x + 1) + j;
                indices[k++] = i * (square_count.x + 1) + j + 1;
            }
        }
    

    // Triangles
    /*
    k = 0;
    for (int i = 0; i < square_count.x + 1; i++)
        for (int j = 0; j < square_count.y + 1; j++)
        {
            if (i < square_count.x && j < square_count.y)
            {
                indices[k++] = i * (square_count.x + 1) + j;
                indices[k++] = (i + 1) * (square_count.x + 1) + j;
                indices[k++] = (i + 1) * (square_count.x + 1) + j + 1;
            
                indices[k++] = i * (square_count.x + 1) + j;
                indices[k++] = (i + 1) * (square_count.x + 1) + j + 1;
                indices[k++] = i * (square_count.x + 1) + j + 1;
            }
        }
    */

    CreateVertexBuffer(m_pVertexBuffer, device, points, points_length);
    CreateIndexBuffer(m_pIndexBuffer, device, indices, indices_length);

    indices_count = indices_length;
}
