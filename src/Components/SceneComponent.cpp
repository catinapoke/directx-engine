#include "SceneComponent.h"

SceneComponent::SceneComponent(std::shared_ptr<RenderData> renderComponent, float x, float y)
{
    renderData = renderComponent;
    position.x = x;
    position.y = y;
}
