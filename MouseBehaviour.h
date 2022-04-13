#pragma once
#include "InputDevice/SimpleMath.h"

typedef DirectX::SimpleMath::Vector2 Vector2;
class InputDevice;

struct CursorData
{
    Vector2 Position;
    Vector2 Offset;
};

class MouseBehaviour
{
public:
    MouseBehaviour(InputDevice* input_device);
    virtual ~MouseBehaviour() = default;

    virtual void UpdateCursorData(CursorData* data) = 0;

protected:
    InputDevice* device;
};

class LockedBehaviour : public MouseBehaviour
{
public:
    explicit LockedBehaviour(InputDevice* input_device)
        : MouseBehaviour(input_device)
    {
    }

    void UpdateCursorData(CursorData* data) override;
};

class UnlockedBehaviour :public MouseBehaviour
{
public:
    explicit UnlockedBehaviour(InputDevice* input_device)
        : MouseBehaviour(input_device)
    {
    }

    void UpdateCursorData(CursorData* data) override;
};