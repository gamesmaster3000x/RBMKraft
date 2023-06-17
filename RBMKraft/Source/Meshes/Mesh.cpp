#include "Mesh.h"

Mesh::Mesh(const void* verts, const unsigned int vertCount, const unsigned int* indices, const unsigned int indexCount) 
{
	if (verts)
	{
		this->vertices = verts;
		this->vertexCount = vertCount;
	}
	else
	{
		static const float arr[] = {
			0.5f, -0.5f, 0.5f,  0.0f, 1.0f,//X+BR
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,//X+BL
			0.5f, 0.5f,  -0.5f, 1.0f, 0.0f,//X+TL
			0.5f, 0.5f,  0.5f,  0.0f, 0.0f,//X+TR

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,//X-BR
			-0.5f, -0.5f, 0.5f,  1.0f, 1.0f,//X-BL
			-0.5f, 0.5f,  0.5f,  1.0f, 0.0f,//X-TL
			-0.5f, 0.5f,  -0.5f, 0.0f, 0.0f,//X-TR

			-0.5f, 0.5f, 0.5f,  0.0f, 1.0f,//Y+BR
			0.5f,  0.5f, 0.5f,  1.0f, 1.0f,//Y+BL
			0.5f,  0.5f, -0.5f, 1.0f, 0.0f,//Y+TL
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f,//Y+TR

			0.5f,  -0.5f, 0.5f,  0.0f, 1.0f,//Y-BR
			-0.5f, -0.5f, 0.5f,  1.0f, 1.0f,//Y-BL
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,//Y-TL
			0.5f,  -0.5f, -0.5f, 0.0f, 0.0f,//Y-TR

			-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,//Z+BR
			0.5f,  -0.5f, 0.5f, 1.0f, 1.0f,//Z+BL
			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,//Z+TL
			-0.5f, 0.5f,  0.5f, 0.0f, 0.0f,//Z+TR

			0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,//Z-BR
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,//Z-BL
			-0.5f, 0.5f,  -0.5f, 1.0f, 0.0f,//Z-TL
			0.5f,  0.5f,  -0.5f, 0.0f, 0.0f,//Z-TR
		};

		this->vertices = arr;
		this->vertexCount = 24;
	}
	
	if (indices)
	{
		this->indices = indices;
		this->indexCount = indexCount;
	}
	else
	{
		static const unsigned int arr[] = {
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};

		this->indices = arr;
		this->indexCount = 36;
	}
}