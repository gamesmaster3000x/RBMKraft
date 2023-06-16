#ifndef MESHSOURCE
#define MESHSOURCE

class Mesh
{
public:
	const float* verts;
	const unsigned int* indices;
	unsigned int vertexCount;

	Mesh(const float* verts = 0, const unsigned int* indices = 0, const unsigned int vertCount = 0);
};

#endif
