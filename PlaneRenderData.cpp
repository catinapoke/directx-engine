#pragma once
#include <vector>
#include "PlaneRenderData.h"
#include "Material.h"

typedef DirectX::SimpleMath::Vector4 Vector4;


PlaneRenderData::PlaneRenderData(ID3D11Device* device, Material* material, Vector2 square_count, float side_length = 10.f)
    :CommonRenderData(material)
{
    std::vector<Vector4> points(2 * (square_count.x + 1) * (square_count.y + 1));
    std::vector<int> indices(2 * (square_count.x + square_count.y + 2 * (square_count.x * square_count.y)));

    for (int y = -(square_count.y * side_length / 2); y <= square_count.y * side_length / 2; y += side_length)
        for (int x = -(square_count.x * side_length / 2); x <= square_count.x * side_length / 2; x += side_length)
        {
            points.push_back(Vector4(x, 0, y, 1)); // position
            points.push_back(Vector4(1, 1, 1, 1)); // color
        }

    for (int i = 0; i < square_count.x + 1; i++)
        for (int j = 0; j < square_count.y + 1; j++)
        {
            if (i < square_count.x)
            {
                indices.push_back(i * (square_count.x + 1) + j);
                indices.push_back((i + 1) * (square_count.x + 1) + j);
            }

            if (j < square_count.y)
            {
                indices.push_back(i * (square_count.x + 1) + j);
                indices.push_back(i * (square_count.x + 1) + j + 1);
            }
        }

    CreateVertexBuffer(m_pVertexBuffer, device, &points[0], points.size());
    CreateIndexBuffer(m_pIndexBuffer, device, &indices[0], indices.size());

    indices_count = std::size(indices);
}
