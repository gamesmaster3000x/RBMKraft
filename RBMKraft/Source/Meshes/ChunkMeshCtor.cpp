#include "ChunkMeshCtor.h"
#include <iostream>

const std::vector<float> ChunkMeshCtor::GetVertexData()
{
	Mesh* mesh = new Mesh();
	size_t bufSize = 0;

	//Get the required buffer size
	for (size_t i = 0; i < CHUNKSIZE * CHUNKSIZE * CHUNKSIZE; i++)
	{
		bufSize += mesh->vertices.size();
		bufSize += mesh->UVs.size();
	}

	//Create buffer of appropriate size
	std::vector<float> buffer = *new std::vector<float>(bufSize);

	size_t offset = 0;
	//Fill the buffer with vert info
	for (size_t z = 0; z < CHUNKSIZE; z++)
	{
		for (size_t y = 0; y < CHUNKSIZE; y++)
		{
			for (size_t x = 0; x < CHUNKSIZE; x++)
			{
				for (size_t i = 0; i < mesh->vertices.size(); i += 3)
				{
					buffer[offset+i] = mesh->vertices[i] + x;
					buffer[offset+i+1] = mesh->vertices[i+1] + y;
					buffer[offset+i+2] = mesh->vertices[i+2] + z;
				}
				offset += mesh->vertices.size();
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
					buffer[offset+i] = mesh->UVs[i];
				}
				offset += mesh->UVs.size();
			}
		}
	}

	return buffer;
}

const std::vector<unsigned int> ChunkMeshCtor::GetIndexData()
{
	Mesh* mesh = new Mesh();
	size_t bufSize = 0;

	//Get the required buffer size
	for (size_t i = 0; i < CHUNKSIZE * CHUNKSIZE * CHUNKSIZE; i++)
	{
		bufSize += mesh->indices.size();
	}

	//Create buffer of appropriate size
	std::vector<unsigned int> buffer = *new std::vector<unsigned int>(bufSize);

	size_t indxOffset = 0;
	size_t ptrOffset = 0;

	//Fill the buffer with vert info
	for (size_t z = 0; z < CHUNKSIZE; z++)
	{
		for (size_t y = 0; y < CHUNKSIZE; y++)
		{
			for (size_t x = 0; x < CHUNKSIZE; x++)
			{
				for (size_t i = 0; i < mesh->indices.size(); i++)
				{
					buffer[ptrOffset+i] = (unsigned int)(mesh->indices[i] + indxOffset);
				}
				ptrOffset += mesh->indices.size();
				indxOffset += mesh->vertices.size() / 3;
			}
		}
	}

	return buffer;
}