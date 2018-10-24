#version 450

in vec2 xy;
in int icharacter;
in vec3 icolor;
out int character;
flat out vec4 color;

void main()
{
	gl_Position = vec4(xy, 0, 1.0);
	character = icharacter;
	color = vec4(icolor, 1.0);
}
