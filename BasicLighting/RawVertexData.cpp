#include "RawVertexData.h"

float* RawVertexData::PyramidData()
{
	float* vertices = new float[9] {
			1, 1,1,
			1, -1,1,
			-1,-1,1,
	};

	return vertices;
}

float* RawVertexData::CubeData()
{
	float* vertices = new float[Cube_Data_Size] {
		   -1, -1, -1,
			1, -1, -1,
			1, 1, -1,
			1, 1, -1,
			-1, 1, -1,
			-1, -1, -1,

			-1, -1, 1,
			1, -1, 1,
			1, 1, 1,
			1, 1, 1,
			-1, 1, 1,
			-1, -1, 1,

			-1, 1, 1,
			-1, 1, -1,
			-1, -1, -1,
			-1, -1, -1,
			-1, -1, 1,
			-1, 1, 1,

			1, 1, 1,
			1, 1, -1,
			1, -1, -1,
			1, -1, -1,
			1, -1, 1,
			1, 1, 1,

			-1, -1, -1,
			1, -1, -1,
			1, -1, 1,
			1, -1, 1,
			-1, -1, 1,
			-1, -1, -1,

			-1, 1, -1,
			1, 1, -1,
			1, 1, 1,
			1, 1, 1,
			-1, 1, 1,
			-1, 1, -1,
	};

	return vertices;
}
