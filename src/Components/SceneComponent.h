#pragma once
#include <memory>
#include <d3d.h>
#include "../RenderData/RenderData.h"
#include "../InputDevice/SimpleMath.h"

typedef DirectX::SimpleMath::Vector4 Vector4;

class SceneComponent
{
public:
    SceneComponent(): position(0, 0, 0, 0) {};
    SceneComponent(std::shared_ptr<RenderData> renderComponent, float x = 0, float y = 0);

    std::shared_ptr<RenderData> GetRenderComponent() { return renderData; }
    Vector4 GetPosition() { return position; }
    void SetPosition(Vector4 pos) { position = pos; }

    void SetX(float x) { position.x = x; }
    void SetY(float y) { position.y = y; }

private:
    std::shared_ptr<RenderData> renderData;
    Vector4 position;
};