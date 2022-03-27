#pragma once
#include <vector>
#include "InputDevice\SimpleMath.h"

struct VertexData {
public:
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector2 texture_coords;
};

class Mesh {
public:
	const std::vector<VertexData> vertices{};
	const std::vector<int> indices{};

	Mesh(std::vector<VertexData> vertices, std::vector<int> indices)
		: vertices(vertices), indices(indices) {}
};