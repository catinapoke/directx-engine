#include "MouseBehaviour.h"
#include "InputDevice/InputDevice.h"

MouseBehaviour::MouseBehaviour(InputDevice* input_device) : device(input_device)
{
}

void LockedBehaviour::UpdateCursorData(CursorData* data)
{
    data->Offset = device->GetCalculatedMousePosition();
    device->SetMousePosition({ 0,0 });
    data->Position = Vector2(0, 0);
}

void UnlockedBehaviour::UpdateCursorData(CursorData* data)
{
    const Vector2 new_position = device->GetCalculatedMousePosition();
    data->Offset = new_position - data->Position;
    data->Position = new_position;
}
