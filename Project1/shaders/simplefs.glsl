#version 330 core
out vec4 fragColor;
uniform float uMoveX;
uniform float uMoveY;
void main()
{
fragColor = vec4(0.567f-uMoveX+uMoveY, 0.674f+uMoveX-uMoveY, 0.234f/uMoveX*uMoveY, 1.0f);
}