#ifndef VERTEX_SIZE
#define VERTEX_SIZE (5 * sizeof(float))
#define INDEX_SIZE sizeof(unsigned int)

#include <vector>

class Mesh
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> UVs;
	
	Mesh(const std::vector<float> verts = *(new std::vector<float>()), const std::vector<unsigned int> indices = *(new std::vector<unsigned int>()), const std::vector<float> UVs = *(new std::vector<float>()));
};

#endif
