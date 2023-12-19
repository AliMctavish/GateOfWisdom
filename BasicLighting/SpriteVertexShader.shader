#version 330 core
layout(location = 0) in vec3 aPos;

//no need to use noramls in sprites bro ! 
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 projection;

out vec2 TexCoords;


void main()
{
	gl_Position = projection *  vec4(aPos.x * 0.01f,aPos.y * 0.01f,aPos.z, 1);
	TexCoords = aTexCoords;
}