#version 410

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

out vec2 uv;
out vec3 normal;
out vec3 pos;

//uniform mat4 meshToWorld;
//uniform mat4 worldToNdc;

//uniform mat4 mesh;
//uniform mat4 camera;
uniform mat4 proj;

void main()
{
    uv = vUV;

    //mat4 transform = worldToNdc * meshToWorld;
    //mat4 transform = proj * camera * mesh;
    mat4 transform = proj;
    normal = vNormal;
    vec4 position = transform * vec4(vPos, 1.0);
    pos = vec3(position);
    gl_Position = position;
}