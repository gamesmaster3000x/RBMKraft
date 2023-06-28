#include "Mesh.h"

Mesh::Mesh(const std::vector<float> verts, const std::vector<unsigned int> indices, const std::vector<float> UVs) 
{
	if (!verts.empty())
	{
		this->vertices = verts;
	}
	else
	{
		float arr[] = {
			0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f,  -0.5f,
			0.5f, 0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f,  0.5f,
			-0.5f, 0.5f,  -0.5f,

			-0.5f, 0.5f, 0.5f,
			0.5f,  0.5f, 0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,

			0.5f,  -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, -0.5f,
			0.5f,  -0.5f, -0.5f,

			-0.5f, -0.5f, 0.5f,
			0.5f,  -0.5f, 0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f, 0.5f,  0.5f,

			0.5f,  -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f,  -0.5f,
			0.5f,  0.5f,  -0.5f,
		};

		for (size_t i = 0; i < sizeof(arr) / sizeof(float); i++)
		{
			this->vertices.push_back(arr[i]);
		}
		this->vertices.shrink_to_fit();
	}
	
	if (!indices.empty())
	{
		this->indices = indices;
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
			20, 22, 23,
		};

		for (size_t i = 0; i < sizeof(arr) / sizeof(unsigned int); i++)
		{
			this->indices.push_back(arr[i]);
		}
		this->indices.shrink_to_fit();
	}

	if (!UVs.empty()) 
	{
		this->UVs = UVs;
	}
	else
	{
		static const float arr[] = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
		};

		for (size_t i = 0; i < sizeof(arr) / sizeof(float); i++)
		{
			this->UVs.push_back(arr[i]);
		}
		this->UVs.shrink_to_fit();
	}
}