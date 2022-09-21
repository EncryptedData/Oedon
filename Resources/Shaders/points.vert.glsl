#version 410

layout(location = 0) in vec3 point;

uniform mat4 proj;

void main()
{
    gl_Position = proj * vec4(point, 1.0);
    gl_PointSize = 5.0;
}
