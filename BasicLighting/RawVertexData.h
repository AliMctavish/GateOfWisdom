#pragma once
#define Cube_Data_Size 180
#define Pyramid_Data_Size 50
#define Cube_With_Normals_And_Texture_Data 288

struct RawVertexData {
	float* PyramidData();
	float* CubeData();
	float* CubeWithNormalsData();
};
