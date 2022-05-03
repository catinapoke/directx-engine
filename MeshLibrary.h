#pragma once
#include <memory>
class Mesh;

class MeshLibrary
{
public:
    static std::shared_ptr<Mesh> GetScreenQuad();
    static std::shared_ptr<Mesh> GetSphere();
    static std::shared_ptr<Mesh> GetCube();

private:
    static std::shared_ptr<Mesh> CreateScreenQuad();
    static std::shared_ptr<Mesh> CreateSphere();
    static std::shared_ptr<Mesh> CreateCube();

private:
    static std::shared_ptr<Mesh> screen_quad;
    static std::shared_ptr<Mesh> cube;
    static std::shared_ptr<Mesh> sphere;
};
