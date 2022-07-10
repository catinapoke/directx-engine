#pragma once

#pragma pack(push, 4)
struct PositionBuffer
{
	float x;
	float y;
	float z;
	float w;
};

struct DisplayBuffer
{
	float x_aspect;
	float y_aspect;
	float buffer_fill_0;
	float buffer_fill_1;
};
#pragma pack(pop)