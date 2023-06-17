#ifndef VERTEX_SIZE
#define VERTEX_SIZE (5 * sizeof(float))
#define INDEX_SIZE sizeof(unsigned int)

class Mesh
{
public:
	const void* vertices;
	const void* indices;
	unsigned int vertexCount;
	unsigned int indexCount;
	
	Mesh(const void* verts = 0, const unsigned int vertCount = 0, const unsigned int* indices = 0, const unsigned int indexCount = 0);
};

#endif
