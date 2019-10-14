#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex_coord;
layout (location = 2) in vec3 in_norm;

out vec3 normal;
out vec2 tex_coord;

void main()
{
    gl_Position = vec4(in_pos, 1.0);
    normal = in_norm;
    tex_coord = in_tex_coord;
}