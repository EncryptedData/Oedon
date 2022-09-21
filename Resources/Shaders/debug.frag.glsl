#version 410

in vec3 pos;
in vec3 normal;
in vec2 uv;
out vec4 color;

uniform vec4 debugColor;

void main()
{
    color = debugColor;
    //color = debugColor;

}