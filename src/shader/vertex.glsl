#version 450

out int id;
out int alive;

void main()
{
    id = gl_VertexID;
    alive = 1;
}
