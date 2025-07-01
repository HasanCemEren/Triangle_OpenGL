#version 330 core
layout (location = 0) in vec3 inPosition;
uniform float uMoveX;
uniform float uMoveY;
void main()
{
gl_Position = vec4(inPosition+vec3(uMoveX,uMoveY,0.0f), 1.0);
}