#pragma once
#define Flat_Surface_Data_Buffer_With_Texture 48
#define Cube_Data_Buffer 180
#define Pyramid_Data_Buffer 50
#define Cube_With_Normals_And_Texture_Data_Buffer_Size 288
#include <array>

struct RawVertexData {
	static const int size = 20;
	std::array<float, Pyramid_Data_Buffer>  PyramidData();
	std::array<float, Cube_Data_Buffer> CubeData();
	std::array<float, Flat_Surface_Data_Buffer_With_Texture> FlatSurface();
	std::array<float, Cube_With_Normals_And_Texture_Data_Buffer_Size> CubeWithNormalsData();
};
