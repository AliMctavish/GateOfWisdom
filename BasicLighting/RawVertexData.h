#pragma once
#define Cube_Data_Size 180
#define Pyramid_Data_Size 50
#define Cube_With_Normals_Data 216

struct RawVertexData {
	float* PyramidData();
	float* CubeData();
	float* CubeWithNormalsData();
};
