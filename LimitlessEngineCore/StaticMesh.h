#pragma once
#include <vector>
#include "VertexTypes.h"

class StaticMesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:
	StaticMesh();
	~StaticMesh();

	void setVertices(std::vector<Vertex> vertices);
	void setIndices(std::vector<unsigned int> indices);
	Vertex* getVertexData();
	unsigned int* getIndexData();
	size_t getVertexCount();
	size_t getIndicesCount();
};

