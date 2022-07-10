#include "MeshLibrary.h"
#include "Mesh.h"
#include "MeshLoader.h"

std::shared_ptr<Mesh> MeshLibrary::screen_quad;
std::shared_ptr<Mesh> MeshLibrary::cube;
std::shared_ptr<Mesh> MeshLibrary::sphere;

std::shared_ptr<Mesh> MeshLibrary::GetScreenQuad()
{
    if (screen_quad.get() == nullptr)
        screen_quad = CreateScreenQuad();

    return screen_quad;
}

std::shared_ptr<Mesh> MeshLibrary::GetSphere()
{
    if (sphere.get() == nullptr)
        sphere = CreateSphere();

    return sphere;
}

std::shared_ptr<Mesh> MeshLibrary::GetCube()
{
    if (cube.get() == nullptr)
        cube = CreateCube();

    return cube;
}

std::shared_ptr<Mesh> MeshLibrary::CreateScreenQuad()
{
    const DirectX::XMFLOAT3 points[4] =
    {
        DirectX::XMFLOAT3(-1, -1, 0),
        DirectX::XMFLOAT3(-1, 1, 0),
        DirectX::XMFLOAT3(1, 1, 0),
        DirectX::XMFLOAT3(1, -1, 0)
    };

    const int indices[6] = {
        0, 1, 2,
        0, 2, 3,
    };

    std::vector<VertexData> vertices = {};
    for (int i = 0; i < std::size(points); i++)
    {
        vertices.push_back(VertexData(points[i]));
    }

    std::vector<int> indices_arr = {};
    for (int i = 0; i < std::size(indices); i++)
    {
        indices_arr.push_back(indices[i]);
    }

    return std::make_shared<Mesh>(vertices, indices_arr);
}

std::shared_ptr<Mesh> MeshLibrary::CreateSphere()
{
    Mesh* sphere = MeshLoader::LoadFirst("Meshes/sphere.obj");
    return std::shared_ptr<Mesh>(sphere);
}

std::shared_ptr<Mesh> MeshLibrary::CreateCube()
{
    //Vertex buffer
    const DirectX::XMFLOAT3 points[24] =
    {
        DirectX::XMFLOAT3(1.f, 1.f, -1.f),
        DirectX::XMFLOAT3(-1.f, 1.f, -1.f),
        DirectX::XMFLOAT3(-1.f, 1.f, 1.f),
        DirectX::XMFLOAT3(1.f, 1.f, 1.f),
        DirectX::XMFLOAT3(1.f, -1.f, 1.f),
        DirectX::XMFLOAT3(1.f, 1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, 1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, -1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, -1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, 1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, 1.f, -1.f),
        DirectX::XMFLOAT3(-1.f, -1.f, -1.f),
        DirectX::XMFLOAT3(-1.f, -1.f, -1.f),
        DirectX::XMFLOAT3(1.f, -1.f, -1.f),
        DirectX::XMFLOAT3(1.f, -1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, -1.f, 1.f),
        DirectX::XMFLOAT3(1.f, -1.f, -1.f),
        DirectX::XMFLOAT3(1.f, 1.f, -1.f),
        DirectX::XMFLOAT3(1.f, 1.f, 1.f),
        DirectX::XMFLOAT3(1.f, -1.f, 1.f),
        DirectX::XMFLOAT3(-1.f, -1.f, -1.f),
        DirectX::XMFLOAT3(-1.f, 1.f, -1.f),
        DirectX::XMFLOAT3(1.f, 1.f, -1.f),
        DirectX::XMFLOAT3(1.f, -1.f, -1.f)
    };

    const DirectX::XMFLOAT2 uvs[24] =
    {
        DirectX::XMFLOAT2(0.625f, 0.5f),
        DirectX::XMFLOAT2(0.875f, 0.5f),
        DirectX::XMFLOAT2(0.875f, 0.25f),
        DirectX::XMFLOAT2(0.625f, 0.25f),
        DirectX::XMFLOAT2(0.375f, 0.25f),
        DirectX::XMFLOAT2(0.625f, 0.25f),
        DirectX::XMFLOAT2(0.625f, 0.f),
        DirectX::XMFLOAT2(0.375f, 0.f),
        DirectX::XMFLOAT2(0.375f, 1.f),
        DirectX::XMFLOAT2(0.625f, 1.f),
        DirectX::XMFLOAT2(0.625f, 0.75f),
        DirectX::XMFLOAT2(0.375f, 0.75f),
        DirectX::XMFLOAT2(0.125f, 0.5f),
        DirectX::XMFLOAT2(0.375f, 0.5f),
        DirectX::XMFLOAT2(0.375f, 0.25f),
        DirectX::XMFLOAT2(0.125f, 0.25f),
        DirectX::XMFLOAT2(0.375f, 0.5f),
        DirectX::XMFLOAT2(0.625f, 0.5f),
        DirectX::XMFLOAT2(0.625f, 0.25f),
        DirectX::XMFLOAT2(0.375f, 0.25f),
        DirectX::XMFLOAT2(0.375f, 0.75f),
        DirectX::XMFLOAT2(0.625f, 0.75f),
        DirectX::XMFLOAT2(0.625f, 0.5f),
        DirectX::XMFLOAT2(0.375f, 0.5f)
    };

    const DirectX::XMFLOAT3 normals[24] =
    {
        DirectX::XMFLOAT3(-0.f, 1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, 1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, 1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, 1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, -0.f, 1.f),
        DirectX::XMFLOAT3(-0.f, -0.f, 1.f),
        DirectX::XMFLOAT3(-0.f, -0.f, 1.f),
        DirectX::XMFLOAT3(-0.f, -0.f, 1.f),
        DirectX::XMFLOAT3(-1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(-1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(-1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(-1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(-0.f, -1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, -1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, -1.f, -0.f),
        DirectX::XMFLOAT3(-0.f, -1.f, -0.f),
        DirectX::XMFLOAT3(1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(1.f, -0.f, -0.f),
        DirectX::XMFLOAT3(-0.f, -0.f, -1.f),
        DirectX::XMFLOAT3(-0.f, -0.f, -1.f),
        DirectX::XMFLOAT3(-0.f, -0.f, -1.f),
        DirectX::XMFLOAT3(-0.f, -0.f, -1.f)
    };

    // Index buffer
    const int indices[36] = {
        1, 0, 3,
        3, 2, 1,
        5, 4, 7,
        7, 6, 5,
        9, 8, 11,
        11, 10, 9,
        13, 12, 15,
        15, 14, 13,
        17, 16, 19,
        19, 18, 17,
        21, 20, 23,
        23, 22, 21 };

    std::vector<VertexData> vertices = {};
    for (int i = 0; i < std::size(points); i++)
    {
        vertices.push_back(VertexData(points[i], uvs[i], normals[i]));
    }

    std::vector<int> indices_arr = {};
    for (int i = 0; i < std::size(indices); i++)
    {
        indices_arr.push_back(indices[i]);
    }

    return std::make_shared<Mesh>(vertices, indices_arr);
}
