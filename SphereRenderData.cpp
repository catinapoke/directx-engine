#include "SphereRenderData.h"
#include <vector>
#include <map>
#include <array>
#include "InputDevice\SimpleMath.h"
typedef DirectX::SimpleMath::Vector3 Vector3;

void CreateSphere(std::vector<Vector3>* points, std::vector<int>* indices, int subdivisions);

SphereRenderData::SphereRenderData(ID3D11Device* device, Material* material) :CommonRenderData(material)
{
    //Vertex buffer
    //DirectX::XMFLOAT4 points[16] =
    //{
    //    DirectX::XMFLOAT4(-0.5f, 0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), // +Y (top face)
    //    DirectX::XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
    //    DirectX::XMFLOAT4(0.5f, 0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
    //    DirectX::XMFLOAT4(-0.5f, 0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),

    //    DirectX::XMFLOAT4(-0.5f, -0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), // -Y (bottom face)
    //    DirectX::XMFLOAT4(0.5f, -0.5f,  0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
    //    DirectX::XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
    //    DirectX::XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)

    //};

    //// Index buffer
    //int indices[36] = { 0, 1, 2,
    //0, 2, 3,

    //4, 5, 6,
    //4, 6, 7,

    //3, 2, 5,
    //3, 5, 4,

    //2, 1, 6,
    //2, 6, 5,

    //1, 7, 6,
    //1, 0, 7,

    //0, 3, 4,
    //0, 4, 7 };

    std::vector<Vector3>* points = new std::vector<Vector3>();
    std::vector<int>* indixs = new std::vector<int>();

    CreateSphere(points, indixs, 3);

    DirectX::XMFLOAT4* points_array = new DirectX::XMFLOAT4[points->size() * 2];
    int* indices = new int[indixs->size()];

    for (int i = 0; i < points->size(); i++)
    {
        Vector3 point = (*points)[i];
        points_array[2 * i] = DirectX::XMFLOAT4(point.x, point.y, point.z, 1);
        points_array[2 * i + 1] = DirectX::XMFLOAT4(1, 1, 1, 1);
    }

    for (int i = 0; i < indixs->size(); i++)
    {
        indices[i] = (*indixs)[i];
    }

    CreateVertexBuffer(m_pVertexBuffer, device, points_array, points->size());
    CreateIndexBuffer(m_pIndexBuffer, device, indices, indixs->size());

    indices_count = indixs->size();
}

using Lookup = std::map<std::pair<int, int>, int>;


int VertexForEdge(Lookup& lookup, std::vector<Vector3>& vertices, int first, int second)
{
    Lookup::key_type key(first, second);

    if (key.first > key.second) {
        std::swap(key.first, key.second);
    }

    const auto inserted = lookup.insert({
        key, vertices.size()
        });

    if (inserted.second)
    {
        Vector3& edge0 = vertices[first];
        Vector3& edge1 = vertices[second];
        Vector3 point = (edge0 + edge1);
        point.Normalize();
        vertices.push_back(point);
    }

    return inserted.first->second;
}

std::vector<int> subdivide(std::vector<Vector3>* vertices, std::vector<int> triangles)
{
    Lookup lookup;
    std::vector<int> result;

    for (int i = 0; i < triangles.size(); i += 3) {
        std::array<int, 3> triangle = {
            triangles[i],
            triangles[i + 1],
            triangles[i + 2]
        };

        std::array<int, 3> mid;

        for (int edge = 0; edge < 3; ++edge)
        {
            mid[edge] = VertexForEdge(
                lookup,
                *vertices,
                triangle[edge],
                triangle[(edge + 1) % 3]);
        }

        result.push_back(triangle[0]);
        result.push_back(mid[0]);
        result.push_back(mid[2]);

        result.push_back(triangle[1]);
        result.push_back(mid[1]);
        result.push_back(mid[0]);

        result.push_back(triangle[2]);
        result.push_back(mid[2]);
        result.push_back(mid[1]);

        result.push_back(mid[0]);
        result.push_back(mid[1]);
        result.push_back(mid[2]);
    }

    return result;
}

void CreateSphere(std::vector<Vector3>* points, std::vector<int>* indices, int subdivisions) {
    const float x = 0.525731112119133606f;
    const float z = 0.850650808352039932f;
    const float n = 0.f;

    *points = std::vector<Vector3>{
        Vector3(-x, n, z), Vector3(x, n, z), Vector3(-x, n,-z),
        Vector3(x, n,-z), Vector3(n, z, x), Vector3(n, z,-x),
        Vector3(n,-z, x), Vector3(n,-z,-x), Vector3(z, x, n),
        Vector3(-z, x, n), Vector3(z,-x, n), Vector3(-z,-x, n)
    };

    *indices = std::vector<int>{
        0, 4, 1,	0, 9, 4,	9, 5, 4,	4, 5, 8,	4, 8, 1,
        8, 10, 1,	8, 3, 10,	5, 3, 8,	5, 2, 3,	2, 7, 3,
        7, 10, 3,	7, 6, 10,	7, 11, 6,	11, 0, 6,	0, 1, 6,
        6, 1, 10,	9, 0, 11, 	9, 11, 2,	9, 2, 5, 	7, 2, 11
    };

    for (int i = 0; i < subdivisions; ++i)
    {
        *indices = subdivide(points, *indices);
    }
}