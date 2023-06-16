#include "Mesh.h"

Mesh::Mesh(const float* verts, const unsigned int* indices, const unsigned int vertCount)
{
	if (verts) {
		this->verts = verts;
		this->vertexCount = vertCount;
	}
	else
	{
		const float v[] = { //(X, Y, Z), Brightness, (UVX, UVY) 
			0.5f,  -0.5f, 0.0f, 1.0f, 1.0f,//BR
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,//BL
			-0.5f, 0.5f,  0.0f, 0.0f, 0.0f,//TL
			0.5f,  0.5f,  0.0f, 1.0f, 0.0f //TR
		};

		this->verts = v;
		this->vertexCount = 0;
	}

	if (indices)
	{
		this->indices = indices;
	}
	else 
	{
		const unsigned int i[] = {
			0, 1, 2,
			0, 2, 3
		};

		this->indices = i;
	}
}
