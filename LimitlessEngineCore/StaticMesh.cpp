#include "stdafx.h"
#include "StaticMesh.h"


StaticMesh::StaticMesh()
{
}


StaticMesh::~StaticMesh()
{
}

void StaticMesh::setVertices(std::vector<Vertex> vertices)
{
	using std::swap;
	swap(this->vertices, vertices);
}

void StaticMesh::setIndices(std::vector<unsigned int> indices)
{
	using std::swap;
	swap(this->indices, indices);
}

Vertex* StaticMesh::getVertexData()
{
	return this->vertices.data();
}

unsigned int* StaticMesh::getIndexData()
{
	return this->indices.data();
}

size_t StaticMesh::getVertexCount()
{
	return this->vertices.size();
}

size_t StaticMesh::getIndicesCount()
{
	return this->indices.size();
}
