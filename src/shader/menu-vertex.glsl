#version 450

flat out vec4 color;

void main()
{
	gl_Position = vec4(0, 0, 0, 1.0);
	color = vec4(0.25, 0.25, 0.25, 1.0);
}
