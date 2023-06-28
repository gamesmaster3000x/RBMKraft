#ifndef CHUNKSIZE
#define CHUNKSIZE 32

#include <Meshes/Mesh.h>

class ChunkMeshCtor
{
public:
	const std::vector<float> GetVertexData();
	const std::vector<unsigned int> GetIndexData();
};

#endif
