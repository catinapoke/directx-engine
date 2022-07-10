#pragma once
#include <vector>
#include "../InputDevice/SimpleMath.h"

struct VertexData {
public:
	VertexData(DirectX::SimpleMath::Vector3 pos = {0,0,0}, 
		DirectX::SimpleMath::Vector2 uv = {0,0}, 
		DirectX::SimpleMath::Vector3 normals = { 0,0,0 })
	{
		position = pos;
		texture_coords = uv;
		normal = normals;
	}

	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector2 texture_coords;
	DirectX::SimpleMath::Vector3 normal;
};

class Mesh {
public:
	const std::vector<VertexData> vertices{};
	const std::vector<int> indices{};

	Mesh(std::vector<VertexData> vertices, std::vector<int> indices)
		: vertices(vertices), indices(indices) {}
};