#pragma once
#include <d3d11.h>
#include <memory>
class DeviceResources;
class RenderTexture;

class GeometryBuffer
{
public:
    GeometryBuffer(std::shared_ptr<DeviceResources> resources);

    void PrepareDeferredRender();
    void SetTextures() const;

protected:
    RenderTexture* position; // pos + shininess
    RenderTexture* color; // albedo + specular
    RenderTexture* normals;

    ID3D11RenderTargetView** render_targets;

    std::shared_ptr<DeviceResources> resources_;
};
