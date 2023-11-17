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

float* RawVertexData::CubeWithNormalsData()
{
	float textureSize = 7.0f;
	float* vertices = new float[Cube_With_Normals_And_Texture_Data]{
	//COORDINATES VEC3    //NORAMALS VEC3    //TEXUTRE VEC2
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, textureSize, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, textureSize, textureSize,   //Face 1 front
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, textureSize, textureSize,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, textureSize,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, textureSize, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, textureSize, textureSize,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, textureSize, textureSize,  //Face 2 back
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, textureSize,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, textureSize, textureSize,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, textureSize,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  //Face 3 left
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, textureSize, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, textureSize, textureSize,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, textureSize, textureSize,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, textureSize,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  //Face 4 right
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, textureSize, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, textureSize, textureSize,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, textureSize, textureSize,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, textureSize,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,  //Face 5 top
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, textureSize, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, textureSize, textureSize,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, textureSize, textureSize,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, textureSize,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,  //Face 6 button
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, textureSize, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, textureSize, textureSize,
	};

	return vertices;
}
