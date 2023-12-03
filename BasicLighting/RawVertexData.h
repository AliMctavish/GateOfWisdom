#pragma once
#define Flat_Surface_Data_Buffer_With_Texture 48
#define Cube_Data_Buffer 180
#define Pyramid_Data_Buffer 50
#define Cube_With_Normals_And_Texture_Data_Buffer 288

struct RawVertexData {
	const int dataSize = Cube_With_Normals_And_Texture_Data_Buffer;
	float* PyramidData();
	float* CubeData();
	float* FlatSurface();
	float* CubeWithNormalsData();
};
