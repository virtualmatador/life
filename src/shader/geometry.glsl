#version 450
layout(points) in;
layout(points, max_vertices = 1) out;
uniform int width;
uniform int height;
in int id[];
in int alive[];
flat out vec4 color;
void main()
{
   gl_Position = vec4(
        (1.5 + mod(id[0], width)) / (width + 2.0) * 2.0 - 1.0,
        ((height + 2.0) - (1.5 + id[0] / width)) / (height + 2.0) * 2.0 - 1.0,
        0.0, 1.0);
    color = vec4(0.25, alive[0], 0.25, 1.0);
    EmitVertex();
    EndPrimitive();
}
