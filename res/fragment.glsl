#version 410

out vec4 out_color;
uniform vec2 my_uniform_variable;

void main()
{
    out_color = vec4(vec3(0.75 + my_uniform_variable.x, 0.5 + my_uniform_variable.x, 0.5 + my_uniform_variable.x), 1.);
}