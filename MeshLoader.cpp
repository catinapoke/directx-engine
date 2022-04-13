#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "MeshLoader.h"



HRESULT MeshLoader::Load(std::vector<Mesh>& model, const std::string& path) {
	model.clear();
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
		std::cout << importer.GetErrorString() << std::endl;
		return E_FAIL;
	}

	ProcessNodesRecursive(model, scene, scene->mRootNode);
	return S_OK;
}

Mesh* MeshLoader::LoadFirst(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FlipWindingOrder);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
		std::cout << importer.GetErrorString() << std::endl;
		return nullptr;
	}

	return ConvertMeshDynamic(scene->mMeshes[0]); //scene->mRootNode->mMeshes[0]
}

void MeshLoader::ProcessNodesRecursive(std::vector<Mesh>& model, const aiScene* scene, const aiNode* node) {
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model.push_back(ConvertMesh(mesh));
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNodesRecursive(model, scene, node->mChildren[i]);
	}
}

Mesh MeshLoader::ConvertMesh(const aiMesh* mesh)
{
	std::vector<VertexData> vertices;
	std::vector<int> indices;

	GetMeshData(mesh, vertices, indices);

	return Mesh(vertices, indices);
}

Mesh* MeshLoader::ConvertMeshDynamic(const aiMesh* mesh)
{
	std::vector<VertexData> vertices;
	std::vector<int> indices;

	GetMeshData(mesh, vertices, indices);

	return new Mesh(vertices, indices);
}

void MeshLoader::GetMeshData(const aiMesh* mesh, std::vector<VertexData>& vertices, std::vector<int>& indices)
{
	using namespace DirectX::SimpleMath;

	// TODO: normals
	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		VertexData vertex;

		vertex.position = Vector3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		/*
		if (mesh->HasNormals()) {
			vertex.normal = Vector3{
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			};
		}
		*/

		vertex.texture_coords =
			(mesh->mTextureCoords[0] != nullptr)
			? Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)
			: Vector2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		const aiFace face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}
}
