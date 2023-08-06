#version 330 core
layout (location = 0) in vec3 vecPos;
layout (location = 1) in vec3 colorVal;
uniform float Xoffset;
uniform float Yoffset;

void main()
{
gl_Position = vec4(vecPos.x + Xoffset,vecPos.y +Yoffset , vecPos.z ,1);
}