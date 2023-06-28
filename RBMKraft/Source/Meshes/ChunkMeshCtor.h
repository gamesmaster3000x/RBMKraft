#ifndef CHUNKSIZE
#define CHUNKSIZE 32

#include <Meshes/Mesh.h>

struct VertBuffer
{
	std::vector<float> ptr;
	size_t size;
};

struct IndxBuffer
{
	std::vector<unsigned int> ptr;
	size_t size;
};

class ChunkMeshCtor
{
public:
	const VertBuffer GetVertexData();
	const IndxBuffer GetIndexData();
};

#endif
