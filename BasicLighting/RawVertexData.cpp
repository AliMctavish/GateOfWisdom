#include "RawVertexData.h"

std::array<float, Pyramid_Data_Buffer> RawVertexData::PyramidData()
{
	std::array<float, Pyramid_Data_Buffer> vertices = {
			1, 1,1,
			1, -1,1,
			-1,-1,1,
	};
	return vertices;
}

std::array<float, Cube_Data_Buffer>  RawVertexData::CubeData()
{
	std::array<float, Cube_Data_Buffer> vertices = {
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


std::array<float, Flat_Surface_Data_Buffer_With_Texture> RawVertexData::FlatSurface()
{
	float textureSize = 1.0f;

	std::array<float, Flat_Surface_Data_Buffer_With_Texture> verticese = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, textureSize, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, textureSize, textureSize,   //Face 1 front
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, textureSize, textureSize,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, textureSize,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};


	return verticese;
}

std::array<float, Cube_With_Normals_And_Texture_Data_Buffer_Size> RawVertexData::CubeWithNormalsData()
{
	float textureSize = 1.0f;
	std::array<float, Cube_With_Normals_And_Texture_Data_Buffer_Size> vertices ={
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
