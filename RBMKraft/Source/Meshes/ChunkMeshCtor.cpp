#include "ChunkMeshCtor.h"
#include <iostream>

const VertBuffer ChunkMeshCtor::GetVertexData()
{
	Mesh* mesh = new Mesh();
	size_t bufSize = 0;
	VertBuffer buf = { *new std::vector<float>, 0};

	//Get the required buffer size
	for (size_t i = 0; i < CHUNKSIZE * CHUNKSIZE * CHUNKSIZE; i++)
	{
		bufSize += mesh->vertices.size();
		bufSize += mesh->UVs.size();
	}

	//Create buffer of appropriate size
	std::vector<float> buffer = *new std::vector<float>;


	//Fill the buffer with vert info
	for (size_t z = 0; z < CHUNKSIZE; z++)
	{
		for (size_t y = 0; y < CHUNKSIZE; y++)
		{
			for (size_t x = 0; x < CHUNKSIZE; x++)
			{
				for (size_t i = 0; i < mesh->vertices.size(); i += 3)
				{
					buffer.push_back(mesh->vertices[i] + x);
					buffer.push_back(mesh->vertices[i+1] + y);
					buffer.push_back(mesh->vertices[i+2] + z);
				}
			}
		}
	}

	for (size_t z = 0; z < CHUNKSIZE; z++)
	{
		for (size_t y = 0; y < CHUNKSIZE; y++)
		{
			for (size_t x = 0; x < CHUNKSIZE; x++)
			{
				for (size_t i = 0; i < mesh->UVs.size(); i++)
				{
					buffer.push_back(mesh->UVs[i]);
				}
			}
		}
	}

	//Populate the buffer object

	buf.ptr = buffer;
	buf.size = bufSize * sizeof(float);

	return buf;
}

const IndxBuffer ChunkMeshCtor::GetIndexData()
{
	Mesh* mesh = new Mesh();
	size_t bufSize = 0;
	IndxBuffer buf = { *new std::vector<unsigned int>, 0 };

	//Get the required buffer size
	for (size_t i = 0; i < CHUNKSIZE * CHUNKSIZE * CHUNKSIZE; i++)
	{
		bufSize += mesh->indices.size();
	}

	//Create buffer of appropriate size
	std::vector<unsigned int> buffer = *new std::vector<unsigned int>;

	unsigned int indxOffset = 0;

	//Fill the buffer with vert info
	for (size_t z = 0; z < CHUNKSIZE; z++)
	{
		for (size_t y = 0; y < CHUNKSIZE; y++)
		{
			for (size_t x = 0; x < CHUNKSIZE; x++)
			{
				for (size_t i = 0; i < mesh->indices.size(); i++)
				{
					buffer.push_back(mesh->indices[i] + indxOffset);
				}
				indxOffset += mesh->vertices.size() / 3;
			}
		}
	}

	//Populate the buffer object

	buf.ptr = buffer;
	buf.size = bufSize * sizeof(unsigned int);

	return buf;
}