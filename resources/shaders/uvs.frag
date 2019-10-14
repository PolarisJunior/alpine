#version 330 core
in vec3 normal;
in vec2 tex_coord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(tex_coord.rg, 0.0f, 1.0f);
}