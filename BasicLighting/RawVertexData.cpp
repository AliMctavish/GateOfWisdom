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
	float* vertices = new float[Cube_Data_Buffer] {
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


float* RawVertexData::FlatSurface()
{
	float textureSize = 1.0f;

	float* verticese = new float[Flat_Surface_Data_Buffer_With_Texture] {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, textureSize, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, textureSize, textureSize,   //Face 1 front
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, textureSize, textureSize,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, textureSize,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};


	return verticese;
}

float* RawVertexData::CubeWithNormalsData()
{
	float textureSize = 1.0f;
	float* vertices = new float[Cube_With_Normals_And_Texture_Data_Buffer]{
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
