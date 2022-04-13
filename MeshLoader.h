#pragma once
#include <assimp/scene.h>
#include <winerror.h>
#include "Mesh.h"

class MeshLoader
{
public:
	static HRESULT Load(std::vector<Mesh>& meshes, const std::string& path);
	static Mesh* LoadFirst(const std::string& path);

private:
	static void ProcessNodesRecursive(std::vector<Mesh>& model, const aiScene* scene, const aiNode* node);
	
	static Mesh ConvertMesh(const aiMesh* mesh);
	static Mesh* ConvertMeshDynamic(const aiMesh* mesh);

	static void GetMeshData(const aiMesh* mesh, std::vector<VertexData>& vertices, std::vector<int>& indices);
};